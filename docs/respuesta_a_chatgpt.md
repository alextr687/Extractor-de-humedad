Pedí a ChatGPT una crítica exhaustiva al proyecto, con el siguiente prompt:

# Pregunta

Quiero que realices una **evaluación técnica completa, crítica y objetiva de este proyecto**. No quiero una valoración superficial ni que simplemente destaques lo positivo. Quiero que intentes detectar problemas, puntos débiles, errores de diseño, decisiones mejorables y oportunidades de mejora, pero sin proponer cambios por el mero hecho de cambiar algo.

### 1\. Comprensión del proyecto

Antes de evaluarlo, reconstruye mentalmente el proyecto a partir de toda la información que te proporcione.

Identifica:

-   Objetivo principal.
-   Objetivos secundarios.
-   Requisitos y restricciones.
-   Arquitectura general.
-   Principio de funcionamiento.
-   Componentes y materiales.
-   Diseño mecánico.
-   Diseño eléctrico/electrónico.
-   Software, si lo hay.
-   Proceso de fabricación y montaje.
-   Uso previsto y condiciones de funcionamiento.

Si existe información insuficiente para entender correctamente alguna parte importante, indícalo explícitamente en lugar de asumirla.

### 2\. Evaluación técnica

Analiza por separado:

**Diseño funcional**

-   Si cumple realmente el objetivo planteado.
-   Robustez del funcionamiento.
-   Posibles modos de fallo.
-   Comportamiento en condiciones normales y anómalas.
-   Dependencias o puntos únicos de fallo.

**Diseño eléctrico/electrónico**

-   Dimensionamiento.
-   Tensiones, corrientes y potencias.
-   Protecciones.
-   Calentamiento y disipación.
-   Caídas de tensión.
-   Compatibilidad entre componentes.
-   Seguridad eléctrica.
-   Fiabilidad de conexiones y cableado.

**Diseño mecánico**

-   Resistencia.
-   Rigidez.
-   Uniones.
-   Tolerancias.
-   Concentraciones de tensión.
-   Vibraciones, golpes o cargas relevantes.
-   Protección frente al entorno.
-   Facilidad de montaje y desmontaje.

**Materiales y fabricación**

-   Adecuación de los materiales.
-   Proceso de fabricación.
-   Tolerancias razonables.
-   Limitaciones del proceso utilizado.
-   Repetibilidad.
-   Facilidad de fabricación.
-   Posibles problemas de envejecimiento o degradación.

**Software**, si procede:

-   Arquitectura.
-   Lógica de funcionamiento.
-   Estados y transiciones.
-   Gestión de errores.
-   Temporización.
-   Uso de memoria y recursos.
-   Bloqueos o comportamientos inesperados.
-   Mantenibilidad.

### 3\. Seguridad y fiabilidad

Busca específicamente situaciones en las que el proyecto pueda:

-   Fallar.
-   Dañarse.
-   Provocar daños a otros elementos.
-   Crear un riesgo para las personas.
-   Degradarse con el tiempo.
-   Comportarse de forma distinta a la esperada.

Distingue entre:

-   Problemas demostrados.
-   Riesgos técnicamente plausibles.
-   Posibilidades meramente especulativas.

No presentes una posibilidad hipotética como si fuera un problema real.

### 4\. Cumplimiento técnico y normativo

Cuando sea relevante, analiza las normas, reglamentos o buenas prácticas aplicables.

Si haces referencia a una norma, reglamento o requisito legal:

-   Indica cuál es.
-   Explica qué parte es relevante.
-   No inventes requisitos.
-   Distingue entre obligación normativa y recomendación de diseño.

Si no puedes verificar una cuestión normativa, dilo explícitamente.

### 5\. Análisis de las decisiones de diseño

Para cada decisión importante, intenta determinar:

1.  Qué problema resuelve.
2.  Qué ventajas proporciona.
3.  Qué inconvenientes introduce.
4.  Qué alternativas razonables existen.
5.  En qué condiciones sería preferible cada alternativa.

No presupongas que una alternativa es mejor simplemente porque sea más sofisticada, cara, moderna o técnicamente compleja.

### 6\. Mejoras

Propón mejoras únicamente cuando exista una razón técnica concreta.

Para cada mejora indica:

-   Problema que resuelve.
-   Cambio propuesto.
-   Beneficio esperado.
-   Coste o complejidad adicional.
-   Posibles inconvenientes.
-   Prioridad.

Clasifica las mejoras como:

-   **Crítica:** debería corregirse antes de utilizar el proyecto.
-   **Importante:** mejora significativamente la seguridad, fiabilidad o funcionamiento.
-   **Conveniente:** aporta una mejora razonable, pero no es necesaria.
-   **Opcional:** mejora principalmente aspectos secundarios, estética, comodidad o experimentación.

No propongas cambios si el diseño actual ya es adecuado para su objetivo.

### 7\. Evaluación experimental

Si proporciono mediciones, pruebas o resultados experimentales:

-   Comprueba si las conclusiones están justificadas por los datos.
-   Busca variables no controladas.
-   Analiza errores de medida.
-   Diferencia correlación de causalidad.
-   Comprueba si el número de pruebas es suficiente para la conclusión que se pretende obtener.
-   Propón experimentos adicionales solamente cuando puedan aportar información relevante.

Si hay cálculos, compruébalos.

Si hay datos suficientes, realiza tú mismo los cálculos necesarios para comprobarlos.

### 8\. Iteraciones del diseño

Si proporciono versiones anteriores del proyecto, compara las iteraciones.

Determina:

-   Qué problemas solucionó cada versión.
-   Qué características se conservaron correctamente.
-   Qué compromisos aparecieron.
-   Si alguna modificación empeoró otro aspecto.
-   Si existe alguna mejora que todavía tenga una justificación técnica clara.

No supongas que una versión posterior es necesariamente mejor.

### 9\. Calidad de ingeniería

Evalúa también el proyecto como trabajo de ingeniería:

-   Claridad de requisitos.
-   Trazabilidad entre requisitos y soluciones.
-   Justificación de decisiones.
-   Coherencia entre diseño teórico y construcción real.
-   Documentación.
-   Reproducibilidad.
-   Mantenibilidad.
-   Facilidad de reparación.
-   Escalabilidad o reutilización, cuando sea relevante.
-   Relación entre complejidad y beneficio.

### 10\. Valoración final

Termina con una síntesis estructurada que incluya:

**Fortalezas principales**  
Qué está particularmente bien resuelto y por qué.

**Debilidades principales**  
Qué aspectos presentan problemas o riesgos y por qué.

**Errores o decisiones cuestionables**  
Solo cuando exista una justificación técnica clara.

**Mejoras recomendadas**  
Ordenadas por prioridad, sin convertir la lista en una colección de cambios cosméticos.

**Aspectos que NO modificarías**  
Indica qué decisiones consideras adecuadas y explica por qué. No busques mejoras artificiales.

**Preguntas pendientes**  
Solo las preguntas cuya respuesta pueda cambiar significativamente la evaluación.

### Criterios importantes

Quiero una evaluación **crítica, no complaciente**, pero también **proporcional al objetivo real del proyecto**.

No evalúes un proyecto doméstico como si fuera un producto industrial certificado si ese no es su propósito. Evalúa cada decisión en función de sus requisitos, entorno de uso, coste, complejidad y nivel de exigencia.

No confundas:

-   «Podría hacerse de otra manera» con «está mal diseñado».
-   «Existe una solución más sofisticada» con «la solución actual es inadecuada».
-   «No está certificado» con «es técnicamente inseguro».
-   Preferencias personales con requisitos técnicos.

Cuando critiques una decisión, explica **el mecanismo físico, matemático, eléctrico, mecánico o lógico que justifica la crítica**.

Cuando una conclusión dependa de una suposición, comienza esa línea con **\[Inferencia\]** o **\[No verificado\]**.

Si existen varias soluciones técnicamente válidas, no elijas arbitrariamente una: explica el compromiso entre ellas.

No intentes agradarme ni defender mis decisiones. Tampoco las critiques por defecto. Tu objetivo es determinar, con la información disponible, **qué está bien, qué está mal, qué es mejorable y qué no merece la pena tocar**.

Quiero que señales tanto los problemas que yo pueda no haber detectado como las decisiones que están bien justificadas aunque inicialmente puedan parecer poco convencionales.

Finalmente, si detectas que falta información importante, **pregúntamela antes de emitir una conclusión definitiva sobre ese aspecto**.

A continuación te adjunto toda la documentación del proyecto. Todo el contexto necesario está en el documento llamado README  
Extractor-de-humedad-(GitHub).zip

# Respuesta

Esta es, punto a punto, mi respuesta a la crítica

## 1\. Reconstrucción del proyecto

Desde luego la descripción propuesta es más precisa, pero algo compleja para mi gusto. En cuanto a la reconstrucción, sin comentarios.

## 2\. Arquitectura y funcionamiento

Sin comentarios

## 3\. Lo que está particularmente bien resuelto

Sin comentarios

## 4\. Problemas y puntos débiles importantes

Ahora empieza la parte divertida

### 4.1. \[Crítico\] El watchdog puede provocar reinicios indefinidos sin llegar al apagado seguro

Efectivamente, el watchdog no tiene límite en cuanto a reinicios. Es un problema real que requiere solución. La única medida de contingencia que hay ahora mismo al respecto es el avisador acústico específico para reinicios inesperados por watchdog.

En defensa del código actual, he de decir que no solo no se han producido este tipo de reinicios encadenados, sino que el código en si mismo no permite reinicios por watchdog de ningún tipo, por lo que es un error que no se ha dado nunca.

### 4.2. \[Crítico\] El "tiempo máximo de 60 minutos" no es realmente un máximo global

La intención del tiempo máximo es que el extractor se apague si se da el caso de que no esté ventilando correctamente, y que por lo tanto la humedad no desminuya de forma significativa. Si este fuera el caso, el reinicio del contador de tiempo solamente podría ocurrir un número limitado de veces, pues solamente admite aumentos de humedad, y solamente por encima del 80%.

En el caso de que la humedad no esté disminuyendo por un mal funcionamiento del extractor, y aumente por encima del 80%, la cantidad que puede aumentar, y, por tanto, la cantidad de veces que el controlador puede declarar un aumento y reiniciar el temporizador, está limitada por las propiedades físicas de la instalación.

A pesar de esta explicación, es posible que este sesa un defecto del firmware que requiera de una mejora, aunque es un caso que no pensé como potencialmente peligroso. En mi defensa he de decir que no se ha producido ningún caso de reinicios temporales indefinidos.

### 4.3. La afirmación de "seis lecturas independientes" no es correcta

Efectivamente, este es un fallo mío. Pensaba que efectivamente el sensor enviaba 6 lecturas independientes, pero no me di cuenta de que las lecturas se recibían en grupos de dos. Es un detalle de la documentación que debe corregirse.

En cuanto al otro apunte, las lecturas de ciclos distintos sí que son independientes entre sí, pues ocurren en ciclos de reloj distintos y con tiempo más que suficiente entre ellas. Tanto es así que las lecturas pueden ser (y son) diferentes, por eso requieren filtrado. En esta parte, ChatGPT no se equivoca.

### 4.4. La estimación estadística de la tasa de error está mal planteada

Tiene gracia que lo mencione, pues este error es tan mío como suyo. La tasa la calculó el propio ChatGPT en algún otro chat que ya está perdido. En cualquier caso, no estoy seguro de que tenga razón ahora y no antes, o viceversa. La estimación actual se basa en la interpretación errónea del punto anterior, por lo que me inclino a pensar que la probabilidad actual sea más precisa.

En cualquier caso, no se puede considerar que los errores sean sucesos aleatorios e independientes. La probabilidad de que el sensor falle condicionada a que la medida anterior también sea errónea no puede ser en ningún caso igual a la probabilidad de que falle condicionado a una medida anterior válida. Mi razonamiento es que las condiciones ambientales varían la probabilidad de fallo, por lo que en las condiciones en las que se declara un fallo, el sensor ya es más propenso a fallar. Es una característica digna de un razonamiento y un estudio estadístico más profundo.

### 4.5. El contador de "sensor congelado" puede confundir estabilidad real con fallo

"Puede" no significa que ese sea el caso. En un ambiente naturalmente cambiante como es un baño, en el que bien hay una ducha en proceso, o bien un extractor activado, los parámetros constantes no son esperables en ningún caso. Si bien es verdad que no hay ninguna justificación técnica para los 5 minutos iguales, pues es un valor ajustado a ojo, las pruebas muestran que no me equivocaba. "Podrás criticar mis métodos, pero no mis resultados".

Es más, en un ambiente en que la humedad debe cambiar, el hecho de que no cambie también es mala señal. Si durante 5 minutos con el extractor encendido la humedad no cambia, pueden estar ocurriendo, al menos, cuatro cosas:

- El extractor no está funcionando y la humedad no baja, por lo que no es deseable que permanezca activado.
- El extractor está encendido pero el sensor está congelado, por lo que tampoco es deseable que el controlador permanezca activado.
- El extractor está funconando pero el aire que entra en el baño tiene las mismas características que el que sale. Es una posiblidad un poco ridícula, pero es este caso tampoco debería estar funcionando el sistema.
- El extractor está funcionando correctamente y se está generando exactamente la misma cantidad de vapor. Es una posibilidad teórica, pero experimentalmente descartada

Solamente en un caso es peor el remedio que la enfermedad, mientras que en los otros tres funciona como se esperaría. Además, siendo honestos, es un caso ridículo. Podría mejorarse el comportamiento con otra estructura para la evaluación del sensor, pero sería demasiado código comparado con el poco beneficio que supondría.

### 4.6. `contadorHumedadAlta` tampoco cuenta realmente "2 minutos consecutivos"

Efectivamente, el comentario está sobresimplificado, llegando a ser erróneo. Conviene cambiarlo.

### 4.7. El watchdog está bien planteado, pero el relé tiene una filosofía "fail ON"

El watchdos no tiene filosofía, simplemente reinicia el programa. El estado normal del extractor durante el encendido es ON. Dado que el watchdog solamente puede reiniciar mientras el controlador está encendido, el reinicio devuelve al relé al estado en el que se encontraba, que es ON. No se da el caso de que un relé que estuviese apagado se encienda por culpa del watchdog, pues solo puede reiniciar si el relé ya estaba en ON. En este caso, la crítica no tiene sentido.

## 5\. DHT22: elección y tratamiento

Sin comentarios

## 6\. Diseño eléctrico

### 6.1. Potencia de 5 V

Efectivamente falta por documentar información sobre la fuente. Pero no toda la información es relevante:

-   aislamiento: necesario
-   certificaciones: necesario. En cualquier caso, las fuentes vendidas en la UE por marcas reconocidas son seguras.
-   protección contra cortocircuito: necesario
-   temperatura máxima: fundamentalmente ninguna fuente comercial está limitada por temperaturas para una instalación doméstica. 
-   comportamiento térmico: no se ni qué se supone que significa esto.
-   grado IP: no es relevante. Para una instalación empotrada, como es el caso, la protección IP viene dada por la propia instalación.
-   corriente real disponible: con 5W, la corriente, "real" o "inventada" es de 1A.
-   tipo de montaje: empotrada junto con el resto de la instalación. Aparece indicado en el README
-   si es una fuente apropiada para instalación permanente: obviamente debe serlo, no es necesario que lo indique. Se puede apreciar por el contexto. Sobre todo en la parte que indica que la instalación queda "escondida en el falso techo".

### 6.2. Atención al punto de alimentación del Nano

Efectivamente, hay un error en el esquema. Sin comentarios.

## 7\. Inconsistencia importante: Nano frente a UNO

Efectivamente, esto también es un error del esquema. El esquema está hecho en CADE-SIMU, que solamente dispone del Arduino UNO como símbolo, por lo que es la única forma que tenía para representar el esquema en este programa. Conviene rediseñar el esquema en un programa de electrónica (EasyEDA, fritzing o similar) o en otra aplicación de dibujo, como AutoCAD o similar.

## 8\. Relé y extractor

Dicho mal y pronto, el relé es de Aliexpress, así que a saber que características técnicas tiene. Me gustaría indicar categoría de empleo, pero solamente aparecen indicadas tensión y corriente resistiva máximas (250V, 10A). En cualquier caso, el extractor es uno convendional, de unos 15W, lo que supone, suponiendo un factor de potencia de 0,8, poco más de 80 mA.

## 9\. Protección eléctrica y normativa

Todas las indicaciones son correctas, pero cabe destacar lo siguiente. El reglamento electrotécnico establece, en su Artículo 2, apartado 2, los casos en los que será de obligado cumplimiento. El apartado 6 del mismo artículo, sin embargo, que las prescripciones generales no aplican a instalaciones de muy baja tensión, siempre que su fuente de energía sea autónoma, no se alimenten de redes destinadas a otros suministros, o que tales instalaciones sean absolutamente independientes de las redes de baja tensión con valores por encima de los fijados para tales pequeñas tensiones.

En cuanto a la ITC-BT-27, la única de las indicadas que aplica, no tiene sentido la preocupación, pues se indica claramente que la instalación se ubica en el mismo sitio que otra ya existente y, presumiblemente, ya cumpliendo el reglamento. Inclusive aunque ese no fuera el caso, el cumplimiento o no de la instalación del extractor o del punto de luz no son parte de este proyecto.

Sobre la ITC-BT-51, las instrucciones de instalación del fabricante, en este caso, son las mías, así que me aseguraré de hacerme caso a mi mismo.

## 10\. Un aspecto positivo del esquema eléctrico

Sin comentarios

## 11\. Alimentación y "bleeder resistor"

Sin comentarios

## 12\. Diseño mecánico

El material de fabricación es el PLA. Es un ambiente interior, y la pieza no soporta esfuerzos mecánicos, por lo que es un material válido. La orientación es la que el slicer defina automáticamente (y la obvia para cualquiera que tenga dos dedos de frente), el grosor de la pared viene definido por la geometría, la tolerancia en estas dimensiones es poco importante, pues el material flexa lo suficiente, la fijación es con cinta de doble cara, no hay sistema de alivio de tensión para el cable, aunque puede dejarse una coca rodeando el pin del interior si es preocupante el esfuerzo del conductor (a criterio del instalador). Evidentemente, como se puede apreciar en el diseño, no hay resistencia a la condensación, y el comportamiento al envejecimiento todavía está por ver, aunque no espero ninguna reacción extraordinaria, tratándose de PLA. 

En cuanto a las supuestas protecciones:

- Condensación: no
- Gotas: está montado del revés, no hay gotas
- Polvo: está montado del revés, tampoco hay polvo
- Manipulación accidental: estando en un techo, es poco probable que alguien alce el brazo y toque sin querer un sensor junto a un downlight a 2,55 m del suelo.

## 13\. Posible problema térmico del sensor

Una luminaria LED doméstica moderna no desprende calor significativo, pero el gradiente de temperaturas sí que puede ser significativo. Conviene medirlo.

## 14\. Software: arquitectura

Sin comentarios

## 15\. El contador de fallos no es estrictamente consecutivo

Efectivamente, el comentario es erróneo.

## 16\. El sensor se consulta cada 15 segundos

Este detalle está adecuadamente comentado en el código.

## 17\. Pruebas experimentales

El hecho de que en la prueba B la humedad y la temperatura alcancen máximos más bajos se debe a que el extractor estaba encendido. No son pruebas distintas, las diferencias en las cantidades de vapor generadas son marginales. No se alcanza el mismo máximo porque el extractor limita el aumento. Es parte del efecto que se esperaba ver. Efectivamente, el volumen de datos experimentales es limitado. Conviene mejorar.

Destaco aquí que de "poco esfuerzo" nada. Ducharme mientras el portátil está leyendo datos es sencillo, pero cronometrar cuánto tiempo sale agua, a qué temperatura, y cuánto tiempo cerrado y ventilando está el baño es un coñazo.

## 18\. Las pruebas reales son más interesantes que el A/B

Sin comentarios

## 19\. Pero la prueba de sensor tiene una conclusión estadística demasiado fuerte

Misma crítica que en el [punto 4.4](#44-la-estimación-estadística-de-la-tasa-de-error-está-mal-planteada). Nada más que decir

## 20\. El script `Serial_to_csv.py` tiene problemas de calidad

Efectivamente, el script da vergüenza. Nada más que decir.

## 21\. Documentación

Sin comentarios

## Todo lo demás

Es un resumen y poco más. Todo lo interesante queda dicho.