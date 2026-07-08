#====================== FUNCIONES ======================
def load_name():
    print("Introduzca el nombre del archivo en formato .txt")
    print("No es necesario incluir la extensión")
    aux = False
    while aux == False:
        doc_name = input().strip(".txt")
        doc_name = doc_name.strip()
        try:
            with open(F"{doc_name}.txt", "r") as fichero: pass
            return doc_name
        except FileNotFoundError:
            print(F"No se encuentra el archivo '{doc_name}'")
            print("Vuelva a intentarlo. Recuerde que el archivo debe ser un documento de texto y que debe encontrarse en la misma carpeta que el script.")
            
def load_data(result, doc_name):
    first_line = ['Inicio', 'de', 'programa']
    prev_last_line = ['Humedad', 'por', 'debajo', 'del', 'mÃ\xadnimo.', 'Apagando...']
    last_line =  ['Fin', 'de', 'programa.', 'Que', 'tenga', 'un', 'buen', 'dÃ\xada', ':)']
    delete = ['T:', '-->', 'Temperatura:', '|', 'Humedad', 'relativa:', '|', 'Humedad', 'absoluta:', 'g/m3', '|', 'Lecturas', 'iguales:', '|', 'Fallos', 'acumulados:', '|']
    matrix = []
    try:
        with open(F"{doc_name}.txt", "r") as fichero:
            data = fichero.readlines()
            for element in data:
                matrix.append(element.split())
            for index, line in enumerate(matrix):
                if line == first_line or line == last_line or line == prev_last_line: continue
                if line[3] == "Error":
                    line = [15*index, 0, 0, 0, 0, line[-3]]
                    continue
                if line[0] == "Nuevo": continue
                for item in delete:
                    line.remove(item)
                del line[0]
                line[0] = float(line[0].strip("ÂºC"))
                line[1] = float(line[1].strip("%"))
                line[2] = float(line[2])
                line[3], line[4] = int(line[3]), int(line[4])
                if line[5] == "Esperando...": line[5] = 0
                else: line[5] = 20
                line.insert(0, 15*index)
                print("line", index, "-->", line)
                result.append(line)
        print("Éxito al cargar")
        return matrix
    except Exception as error:
        print("Ha ocurrido el siguiente error", error)
        return

def save_data(result, doc_name):
    header = "TIEMPO,TEMPERATURA,HUMEDAD_REL,HUMEDAD_ABS,IGUALES,FALLOS,ESTADO\n"
    with open(F"{doc_name}.csv", "w") as fichero:
        fichero.write(header)
        for line in result:
            for index,element in enumerate(line):
                fichero.write(str(element))
                if index < 6: fichero.write(",")
            fichero.write("\n")
        print("Éxito al guardar")
        return 1

def main():
    result = []
    doc_name = load_name()
    load_data(result, doc_name)
    print(result)
    save_data(result, doc_name)
    print("Fin de programa. Que tenga un buen día :)")
#====================== MAIN ======================
main()