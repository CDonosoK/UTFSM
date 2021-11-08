import os, re

comandoInsert = "INSERT INTO Estudiantes (Nombre,Rut,Rol,Telefono,Edad) VALUES ('Sebastian Godinez','19991933-8','201673501-1',988881234,21)"
comandoUpdate = "UPDATE Notas SET Nota =54 WHERE Rol = '201673557-4'"
comandoSelect = "SELECT Telefono FROM Estudiantes WHERE Nombre ='Clemente Aguilar'"

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

    def obtenerInformacion(archivo):
        arch = open(archivo + ".csv", "r")
        nombreColumnas = arch.readline()
        nombreColumnas = nombreColumnas.strip().split(",")
        informacionTabla = []
        for linea in arch.readlines():
            linea = linea.strip().split(",")
            informacionTabla.append(linea)
        arch.close()
        return (nombreColumnas, informacionTabla)