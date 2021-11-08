import re, os

#VARIABLES
comandos = ["SELECT","INSERT INTO", "UPDATE"]
comandoInsert = "INSERT INTO Estudiantes (Nombre,Rut,Rol,Telefono,Edad) VALUES ('Sebastian Godinez','19991933-8','201673501-1',988881234,21)"
comandoUpdate = "UPDATE Notas SET Nota =54 WHERE Rol = '201673557-4'"
comandoSelect = "SELECT Telefono FROM Estudiantes WHERE Nombre ='Clemente Aguilar'"
comandoSelect = "SELECT * FROM Estudiantes"

def main():
    Salir = False
    while not Salir:
        eleccionUsuario = int(input("¿Qué desea hacer? \n [1] Ingresar comando \n [2] Salir \n"))

        if eleccionUsuario == 1:
            comandoUsuario = input("Ingrese el comando: ")
            while True:

                if re.search("SELECT", comandoUsuario) != None:
                    if verificarSELECT(comandoSelect):
                        realizarSELECT(comandoSelect)
                    else:
                        print("Error de Sintaxis!")

                elif re.search("UPDATE", comandoUsuario) != None:
                    if verificarUPDATE(comandoUpdate):
                        realizarUPDATE(comandoUsuario)
                    else:
                        print("Error de Sintaxis!")

                elif re.search("INSERT", comandoUsuario) != None:
                    if verificarINSERT(comandoInsert):
                        realizarINSERT(comandoUsuario)
                    else:
                        print("Error de Sintaxis!")
                elif comandoUsuario == '2':
                    break
                else:
                    print("Ha ingresado un comando que no existe")
                comandoUsuario = input("Ingrese: \n [1] Si desea ingresar otro comando \n [2] Si desea salir")
                if comandoUsuario != '2':
                    comandoUsuario = input("Ingrese el comando: ")

        elif eleccionUsuario == 2:
            Salir = True
        else:
            print("Ah ingresado una opción no correcta. Inténtelo nuevamente")

def verificarSELECT(comando):
    comandoBuscar = "SELECT"
    inicio = re.search(comandoBuscar, comando).start()
    final = re.search(comandoBuscar, comando).end()
    if inicio != 0 or final != 6:
        return False
    else:
        pass

def verificarUPDATE(comando):
    comandoBuscar = "UPDATE"
    inicio = re.search(comandoBuscar, comando).start()
    final = re.search(comandoBuscar, comando).end()
    if inicio != 0 or final != 6:
        return False
    else:
        pass

def verificarINSERT(comando):
    comandoBuscar = "INSERT INTO"
    inicio = re.search(comandoBuscar, comando).start()
    final = re.search(comandoBuscar, comando).end()
    if inicio != 0 or final != 11:
        return False
    else:
        pass

def realizarSELECT(comando):
    pass

def realizarUPDATE(comando):
    pass

def realizarINSERT(comando):
    pass

def obtenerInformacion(archivo):
    arch = open(archivo+".csv","r")
    nombreColumnas = arch.readline()
    nombreColumnas = nombreColumnas.strip().split(",")
    informacionTabla = []
    for linea in arch.readlines():
        linea = linea.strip().split(",")
        informacionTabla.append(linea)
    arch.close()
    return (nombreColumnas, informacionTabla)

if __name__ == '__main__':
    main()