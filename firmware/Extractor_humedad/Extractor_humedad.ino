/*====================================================================
CONTROL AUTÓNOMO DE VENTILADOR CON DHT22

Sistema embebido para control de ventilación basado en temperatura
y humedad, con filtrado de lecturas (mediana de 3 muestras) y
máquina de estados robusta frente a fallos del sensor.

Funcionamiento:
- El ventilador arranca activado.
- Se espera un tiempo mínimo antes de evaluar apagado.
- Se decide el apagado por:
    • Humedad absoluta y relativa por debajo del umbral
    • Tiempo máximo de funcionamiento
- Se detectan errores del sensor (lecturas inválidas o congeladas).

Gestión de fallos:
- Primer error: modo seguro con intento de recuperación.
- Si el sensor se recupera, el sistema continúa.
- Error repetido: apagado definitivo por seguridad.

Finalización:
- Apaga el relé del ventilador.
- Desactiva watchdog, ADC y UART.
- Entra en sueño profundo permanente (SLEEP_MODE_PWR_DOWN).

Notas:
- La detección de reset por watchdog requiere bootloader que preserve MCUSR 
  (o programación por ISP).
- Para la versión final debe comentarse la línea: #define DEBUG
====================================================================*/
/*Definición de funciones debug (capa de depuración)
Encapsula Serial.print() con soporte de tipos y PROGMEM, eliminada completamente en compilación sin DEBUG.*/
//#define DEBUG
#ifdef DEBUG
  inline void debug(const char *s) {Serial.print(s);}
  inline void debug(const __FlashStringHelper *s) {Serial.print(s);}
  inline void debug(unsigned long v) {Serial.print(v);}
  inline void debug(int v) {Serial.print(v);}
  inline void debug(float v) {Serial.print(v);}
  inline void debugln(const char *s) {Serial.println(s);}
  inline void debugln(const __FlashStringHelper *s) {Serial.println(s);}
  inline void debugln(unsigned long v) {Serial.println(v);}
  inline void debugln(int v) {Serial.println(v);}
  inline void debugln(float v) {Serial.println(v);}
#else
  inline void debug(...) {}
  inline void debugln(...) {}
#endif
//Configuración
#define AH_LIMITE 13.0 //Humedad absoluta límite (en g/m3)
#define H_LIMITE 65.0 //Humedad relativa límite (en %)
#define RESOLUCION_SENSOR 0.1 
#define MAX_FALLOS 4 //1 minuto continuado sin lecturas válidas
#define MAX_LECTURAS_IGUALES 20 //5 minutos de valores invariantes
#define H_MAXIMA 80.0 //Humedad relativa para reinicio de programa
#define UMBRAL_AUMENTO 0.5 //Pendiente de la humedad para considerar reinicio
#define CICLOS_HUMEDAD_ALTA 8 //2 minuto con humedad relativa aumentando y superior a H_MAXIMA
#define TIMEOUT_SENSOR 600 //Tiempo máximo esperable para obtener respuesta del DHT (600 ms)
const unsigned long TIEMPO_MIN = 900000; //15 minutos
const unsigned long TIEMPO_MAX = 3600000; //60 minutos
const unsigned long INTERVALO = 5000; //5 segundos · 3 lecturas

//Melodías. Importante que cada nota dure menos de 5 segundos
const int melodiaReset[] PROGMEM = {349, 330, 311, 294, 277}; // Fa, Mi, Re#, Re, Do# (5 notas. Melodía especial)
const int duracionesReset[] PROGMEM = {200, 200, 200, 200, 200}; //Todas las notas cortas
const int melodiaTiempo[] PROGMEM = {440, 440, 440}; // La, La, La
const int duracionesTiempo[] PROGMEM = {800, 200, 200}; //Primera nota larga
const int melodiaError[] PROGMEM = {440, 440, 440}; // La, La, La
const int duracionesError[] PROGMEM = {200, 800, 200}; //Segunda nota larga

//Librerías para sensor, sleep, math, lectura memoria flash y watchdog
#include <DHT.h>
#include <avr/sleep.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

//Pines para entradas y salidas
#define RELAY 2 //Relé activo en HIGH
#define BUZZER 5 //Zumbador pasivo para aviso
#define DHTPIN 3 //Sensor de humedad y temperatura DHT22
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//Variables de programa
unsigned long tiempoInicio;
unsigned long ahora;
static unsigned long ultimo = 0;
unsigned long tiempoError;
int contadorFallos = 0;
int contadorIguales = 0;
int contadorHumedadAlta = 0;
float h[3], t[3]; //Estados para la toma de medidas
int faseLectura = 0; //Memoria para la toma de medidas
float prev_humedad = 0; //Memoria para comprobación de medidas idénticas de humedad
float prev_temperatura = 0; //Memoria para comprobación de medidas idénticas de temperatura
bool errorRepetido = false; //Memoria para segunda entrada en etapaError
bool errorTiempoMaximo = false; //Memoria para tiempo máximo en etapaError
unsigned long tiempoLectura = 0; //Tiempo de inicio de la lectura del sensor

//Variables para la máquina de estados
enum estado { etapaEspera, etapaTest, etapaError, etapaHumedad, etapaTiempo, etapaApagado };
estado estadoActual = etapaEspera;

//========================= FUNCIONES ==============================
//Cálculo de la humedad absoluta
float HumedadAbsoluta(float t, float h) {
  float Pv = 6.112 * exp((17.67 * t) / (t + 243.5)); //Cálculo de la presión de vapor a una temperatura T mediante la aproximación de Magnus-Tetens
  return (h * Pv * 2.1674) / (273.15 + t); //Cálculo de la masa de agua mediante PV=nRT
}

//Cálculo de la mediana de tres lecturas consecutivas
float mediana(float a, float b, float c) {
  if (a > b) { float temporal = a; a = b; b = temporal; } //Tras este paso se garantiza a <= b
  if (b > c) { float temporal = b; b = c; c = temporal; } //Tras este paso se garantiza b <= c, pero podría romperse a <= b
  if (a > b) { float temporal = a; a = b; b = temporal; } //Se restaura el orden entre a y el nuevo b. Ahora sí: a <= b <= c
  return b;
}

//Lectura y validación del sensor
//1 para lectura correcta, 0 para lectura en proceso, -1 para error de lectura, -2 para error de rango y -3 para error de tiempo de lectura
//La validación de lecturas se da cada 15 segundos (3 lecturas)
int leerSensor(float &humedad, float &temperatura, float &agua) {
  //Primera lectura
  if (faseLectura == 0) {
    tiempoLectura = millis();
    h[0] = dht.readHumidity();
    t[0] = dht.readTemperature();
    faseLectura = 1; //Se da paso a la siguiente etapa
    //Comprobación del tiempo máximo de lectura. Detecta lecturas anormalmente largas (IMPORTANTE: NO detecta bloqueos en el DHT)
    if (millis() - tiempoLectura > TIMEOUT_SENSOR) return -3; //Si la lectura se alarga más de lo normal, se declara error y se continúa con la siguiente lectura
    //Aunque la lectura cuente como error, si el valor es válido, se sigue considerando para la toma de decisiones
    return 0;
  }
  //Segunda lectura
  if (faseLectura == 1) {
    tiempoLectura = millis();
    h[1] = dht.readHumidity();
    t[1] = dht.readTemperature();
    faseLectura = 2; //Se da paso a la siguiente etapa
    if (millis() - tiempoLectura > TIMEOUT_SENSOR) return -3;
    return 0;
  }
  //Tercera (y última) lectura
  if (faseLectura == 2) {
    tiempoLectura = millis();
    h[2] = dht.readHumidity();
    t[2] = dht.readTemperature();
    faseLectura = 0; //Se vuelve a la etapa inicial
  } 
  //Comprobación de errores de lectura (el error del DHT es NaN)
  if (isnan(h[0]) || isnan(h[1]) || isnan(h[2]) || isnan(t[0]) || isnan(t[1]) || isnan(t[2])) return -1; 
  humedad = mediana(h[0], h[1], h[2]); //Se calcula la mediana de h llamando a la función
  temperatura = mediana(t[0], t[1], t[2]); //Se calcula la mediana de t llamando a la función
  //Comprobación de valores medidos. Se declara error si el valor mediano está fuera de rango (pues los otros dos lo estarán más todavía)
  if (humedad < 0 || humedad > 100 || temperatura < -40 || temperatura > 80) return -2;
  agua = HumedadAbsoluta(temperatura, humedad); //Cálculo de la humedad absoluta llamando a la función
  if (millis() - tiempoLectura > TIMEOUT_SENSOR) return -3; //Si en la tercera lectura el valor se obtiene fuera del tiempo máximo,
  //el valor es validado como siempre, pero se declara error. Los valores siguen siendo válidos para la toma de decisiones
  return 1; //Todo ha salido bien y se devuelve un 1
}

//Imprimir tiempo por monitor serie
void tiempo(unsigned long tiempoActual) {
  unsigned long minutos = tiempoActual / 60000;
  unsigned long segundos = (tiempoActual % 60000) / 1000;
  debug(F("T: ["));
  debug(minutos); debug(F(":"));
  if(segundos < 10) debug(F("0")); //El cero antes de una única unidad
  debug(segundos); debug(F("] --> "));
}

//Imprimir datos por monitor serie
void datos(float humedad, float temperatura, float agua) {
  debug(F("Temperatura: ")); debug(temperatura);
  debug(F("ºC | Humedad relativa: ")); debug(humedad);
  debug(F("% | Humedad absoluta: ")); debug(agua); debug(F(" g/m3"));
}

//Aviso de error en el programa (para cualquier melodía)
void aviso(const int *melodia, const int *duraciones, int n) {
  debug(F("Melodía de error: 𝄞 "));
  for (int i = 0; i < n; i++) {
    int nota = pgm_read_word(&melodia[i]);
    int duracion = pgm_read_word(&duraciones[i]);
    tone(BUZZER, nota, duracion);
    delay(duracion + 50);
    wdt_reset(); //Para evitar reinicios, se despierta el watchdog con cada nota
    if (duracion < 500){debug(F("♪"));} //Es necesario añadir las llaves al if para que cuando desaparezca DEBUG_PRINT el if ejecute algo (en caso contrario aparece el error: 'else' without a previous 'if')
    else debug(F("♩"));
  }
  debugln("");
}

//Mensaje que se imprime por monitor serie (tiempo, datos, contadorIguales, contadorFallos y estado de la máquina)
void info(int variableError, int contadorFallos, int contadorIguales, unsigned long ahora, float humedad, float temperatura, float agua) {
  if (variableError == 1) {
    tiempo(ahora);
    datos(humedad, temperatura, agua);
    debug(F(" | Lecturas iguales: "));
    debug(contadorIguales);
    debug(F(" | Fallos acumulados: "));
    debug(contadorFallos);
  }
  else if (variableError == -1) {
    tiempo(ahora);
    debug(F("Error de lectura. Fallos acumulados: "));
    debug(contadorFallos);
  }
  else if (variableError == -2) {
    tiempo(ahora);
    debug(F("Error de rango. Fallos acumulados: "));
    debug(contadorFallos);
  }
  else if (variableError == -3) {
    tiempo(ahora);
    debug(F("El sensor no responde. Fallos acumulados: "));
    debug(contadorFallos);
  }
}

//Detección de reset por watchdog. Sólo funcionará si el bootloader no borra MCUSR (debe programarse por ISP)
uint8_t mcusr_mirror __attribute__((section(".noinit")));
void get_mcusr(void) __attribute__((section(".init3")));
void get_mcusr(void) {
    mcusr_mirror = MCUSR;
    MCUSR = 0;
    if (mcusr_mirror & (1 << WDRF)) {
        wdt_disable();
    }
}

//========================= MAIN ==============================
void setup() {
  dht.begin();
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(RELAY, HIGH);
  tiempoInicio = millis();
  debugln(F("Inicio de programa"));
  if (mcusr_mirror & (1 << WDRF)) {
    debugln(F("Reset automático por error de ejecución"));
    aviso(melodiaReset, duracionesReset, sizeof(melodiaReset)/sizeof(melodiaReset[0]));
  }
  wdt_enable(WDTO_8S); //Watchdog a 8 segundos
}

void loop() {
  wdt_reset(); //Reset del watchdog
  ahora = millis();
  if (ahora - ultimo < INTERVALO) return; //Tiempo actual por debajo del intervalo (todavía no pasaron 5 segundos desde la última medida)
  ultimo = ahora;
  //Lectura y validación de datos
  float humedad, temperatura, agua;
  int variableError = leerSensor(humedad, temperatura, agua);
  if (variableError == 0) return; //Lectura incompleta (mediana no calculada)
  if (variableError < 0) {
    contadorFallos++;
    if (contadorHumedadAlta > 0) contadorHumedadAlta--; 
    /*Si no hay lectura válida de humedad, se desecha una medida de humedad alta (evidencia débil)
    Es deseable no reiniciar el proceso en la medida de lo posible, por ese motivo las lecturas erróneas descuentan datos de humedad alta.
    Aún así, no son evidencia suficiente de que la humedad se ha reducido de manera efectiva. Ésto se hace así porque no es deseable reiniciar
    el ciclo con un sensor defectuoso o poco fiable (se penalizan lecturas erróneas para el reinicio)*/
  } 
  if (variableError == 1) {
    if (contadorFallos > 0) contadorFallos--; //Descuenta un error por cada lectura correcta (evita lecturas inconsistentes)
    if (fabs(humedad - prev_humedad) < RESOLUCION_SENSOR && fabs(temperatura - prev_temperatura) < RESOLUCION_SENSOR) contadorIguales++;
    else contadorIguales = 0;
    if (humedad > H_MAXIMA) {
        if ((humedad - prev_humedad) >= UMBRAL_AUMENTO) contadorHumedadAlta++; //Si la humedad está por encima del máximo y aumenta, incrementar contador
        //En caso contrario no hace nada (no resetea el contador si la humedad no aumenta pero sigue por encima del máximo)
    } 
    else contadorHumedadAlta = 0; //Si la lectura es inferior a 95, se resetea el contador (evidencia fuerte)
    prev_humedad = humedad;
    prev_temperatura = temperatura;
  }

  switch (estadoActual) {

    case etapaEspera:
      info(variableError, contadorFallos, contadorIguales, ahora, humedad, temperatura, agua);
      debugln(F(" | Esperando..."));
      // Transición. Pasan 15 minutos --> etapaTest
      if (ahora - tiempoInicio >= TIEMPO_MIN) estadoActual = etapaTest;
      break;

    case etapaTest:
      info(variableError, contadorFallos, contadorIguales, ahora, humedad, temperatura, agua);
      debugln(F(" | Evaluando..."));
      // Transicion. Errores máximos --> etapaError. Humedad mínima --> etapaHumedad. Tiempo máximo --> etapaTiempo
      if (ahora - tiempoInicio >= TIEMPO_MAX) estadoActual = etapaTiempo; //Tiempo máximo, comprobación prioritaria
      else if (contadorFallos >= MAX_FALLOS) {
        debugln(F("Número máximo de errores alcanzado. "));
        tiempoError = millis();
        estadoActual = etapaError; //Errores máximos, segunda comprobación
      } 
      else if (contadorIguales >= MAX_LECTURAS_IGUALES) {
        debugln(F("Sensor congelado. "));
        tiempoError = millis();
        estadoActual = etapaError; //Sensor congelado, tercera comprobación
      } 
      else if (variableError < 0) break; //En caso de lectura errónea (y NO tiempo máximo, NO errores máximos), salir de máquina de estados sin transición
      else if (contadorHumedadAlta >= CICLOS_HUMEDAD_ALTA) {
        debugln(F("Nuevo aumento de humedad detectado. Reiniciando temporizador..."));
        tiempoInicio = millis();
        estadoActual = etapaEspera; //Nuevo aumento de humedad
      }
      else if (agua <= AH_LIMITE && humedad <= H_LIMITE) estadoActual = etapaHumedad; //Última comprobación, humedad meta alcanzada
      break;

    case etapaError:
      if (errorRepetido == true || errorTiempoMaximo == true) { 
        debugln(F("Apagando..."));
        aviso(melodiaError, duracionesError, sizeof(melodiaError)/sizeof(melodiaError[0]));
        //Transición obligatoria. Siempre --> etapaApagado
        estadoActual = etapaApagado;
      } else {
        info(variableError, contadorFallos, contadorIguales, ahora, humedad, temperatura, agua);
        debugln(F("Modo seguro..."));
        //Transiciones (dentro de la misma etapa y entre etapas)
        if (ahora - tiempoError >= TIEMPO_MIN) errorTiempoMaximo = true; //Si se vuelve a superar el tiempo mínimo --> errorTiempoMaximo = true --> etapaApagado
        if (contadorFallos == 0) { //Si el sensor se recupera
          estadoActual = etapaTest; //Se vuelve a etapaTest
          errorRepetido = true; //Pero recuerda que ya estuvo en etapaError (la próxima vez apagará directamente)
        }     
      }
      break;

    case etapaHumedad:
      debugln(F("Humedad por debajo del mínimo. Apagando..."));
      //Transición obligatoria. Siempre --> etapaApagado
      estadoActual = etapaApagado;
      break;

    case etapaTiempo:
      debugln(F("Tiempo máximo alcanzado. Apagando..."));
      aviso(melodiaTiempo, duracionesTiempo, sizeof(melodiaTiempo)/sizeof(melodiaTiempo[0]));
      //Transición obligatoria. Siempre --> etapaApagado
      estadoActual = etapaApagado;
      break;

    /*Fin de programa
    La ejecución de etapaApagado bloquea definitivamente el Arduino, sin posibilidad de despertarlo mediante software. */
    case etapaApagado:
      debugln(F("Fin de programa. Que tenga un buen día :)"));
      digitalWrite(RELAY, LOW);
      #ifdef DEBUG
        Serial.flush();
      #endif
      noInterrupts(); //Desactiva todos los procesos en segundo plano (DHT, monitor serie, millis...)
      wdt_disable(); //Desactivar el watchdog para evitar reset
      ADCSRA = 0; //Apaga el Convertidor Analógico-Digital
      UCSR0B = 0; // Desactiva UART completamente (se elimina cualquier comunicación)
      PORTD &= ~(1 << PD2);  // Fuerza a LOW el relé por registro directo
      set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Modo de sueño profundo
      sleep_enable();
      while (true) sleep_cpu(); //En caso de no ejecutarse esta línea, quedará en bucle infinito
      //No hay break. Etapa final 
    
    default:
      debugln(F("Ha ocurrido un error en el programa. Error en la máquina de estados"));
      while (true); //Se espera a la activación del watchdog mediante bucle infinito
  }
}