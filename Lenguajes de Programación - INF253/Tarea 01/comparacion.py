import os.path as path
import sys
sys.stdout.encoding
'UTF-8'

def SELECT(instruccion):
    asterisco = u"*"
    if asterisco in instruccion:
        for tipo in procesado:
            linea = u""
            for elem in tipo:
                linea = linea+" "+elem
            print (linea)
    else:
        cont = 0 
        for elem in procesado[0]:
            if elem in instruccion:
                break
            cont +=1
    for pedazo in procesado:
        print (pedazo[cont])
    return

def UPDATE(instruccion2):

    archivo = open("output.txt","w")
    i = 0 
    j = 0
    igual = u"="
    espacio = u" "
    contenido = []

    for elem in procesado[0]:
        estring = u""
        elem += igual
        if elem in instruccion2:
            n = instruccion2.find(elem)
            m = len(elem)
            o = instruccion2.find(espacio,n)
            i = n+m
            if o==-1:
                while ( i<len(instruccion2) ):
                    estring += instruccion2[i]
                    i += 1
            else :
                while ( i<o ):
                    estring += instruccion2[i]
                    i += 1
            contenido.append([n,m,elem,estring])

    i = 0
    verificador = 0
    contenido.sort()
    print (contenido)
    print (procesado[3][1])

    for elem in procesado[0]:
        if elem in contenido[0][2]:
            verificador = i
        i += 1
    
    i = 0
    for elem in procesado:
        for elem2 in elem:
            if elem2 in contenido[1][3]:
                procesado[i][verificador] = contenido[0][3]
        i+=1
        

    i = 0
    for elem in procesado:
        j = 0
        for hehee in elem:
            archivo.write(hehee)
            if ( j+1!=y ):
                archivo.write(",")
            j+=1
        archivo.write("\n")
        i+=1
    return

y = 0
subprocesado=[]
procesado=[]
palabra = ""
#instruccion = "SELECT Nombre FROM Estudiantes;"
#instruccion2 = "UPDATE Notas SET Nota=54 WHERE Rol='201673557-4';" evaluar el caso con";"
instruccion3 = u"INSERT INTO Estudiantes"

palabra = input("Que desea abrir?\n")
if path.exists(palabra+".csv"):
    archivo = open(palabra+".csv","r")
    LECTURA(palabra,archivo)
    archivo.close()
    INSERT_INTO(instruccion3)
    #UPDATE(instruccion2)
    #SELECT(instruccion)
    
else :
    print ("el archivo no existe\n")