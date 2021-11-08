import os.path as path
import sys
import re


sys.stdout.encoding
'UTF-8'

def LECTURA(palabra,archivo):
    for linea in archivo:
        subprocesado.append(linea.strip().split(","))
    y = len(subprocesado[0])
    
    for elem in subprocesado:
        pormientras = []
        for subelem in elem:
            #u = unicode(subelem,"utf-8")
            #u = subelem.decode("utf-8")
            #CUIDADO CON ESTA LÍNEA
            pormientras.append(subelem)
        procesado.append(pormientras)
    #print (procesado)
    return

def INSERT_INTO ():
    p = []
    a = 0
    x = True
    div = instruccion3.split(u"VALUES")
    div[1] = div[1].replace(u')','').replace(u'(','').replace(u';','')
    print (div)
    for elem in procesado[0]:
        if elem in div[0]:
            p.append(a)
        a += 1
    print (p)
    for elem in procesado:
        if elem[p[0]] in div[1]:
            x = False
    if x:
        temp = []
        for elem in procesado[0]:
            temp.append(u"-")
        procesado.append(temp)
        lim = len(procesado)
        ingreso = div[1].split(u",")
        a = 0
        for digito in p:
            procesado[lim-1][digito] = ingreso[a]
            a += 1
    print (procesado)
    return

def definir_pal():
    se = u"SELECT"
    up = u"UPDATE"
    ii = u"INSERT INTO"
    pal = u""
    primer = [-1,-1]
    continuar = True
    if (se in instruccion3):
        cont = 6
        while continuar:
            if (primer[0]==-1):
                if ((instruccion3[cont] == u" ")and(instruccion3[cont+1] != u" ")):
                    primer[0] = cont+1
            else :
                if ((instruccion3[cont] != u" ")and(instruccion3[cont+1] == u" ")):
                    primer[1] = cont+1
                    continuar = False
            cont += 1
    if (up in instruccion3):
        cont = 6
        while continuar:
            if (primer[0]==-1):
                if ((instruccion3[cont] == u" ")and(instruccion3[cont+1] != u" ")):
                    primer[0] = cont+1
            else :
                if ((instruccion3[cont] != u" ")and(instruccion3[cont+1] == u" ")):
                    primer[1] = cont+1
                    continuar = False
            cont += 1
    if (ii in instruccion3):
        cont = 11
        while continuar:
            if (primer[0]==-1):
                if ((instruccion3[cont] == u" ")and(instruccion3[cont+1] != u" ")):
                    primer[0] = cont+1
            else :
                if ((instruccion3[cont] != u" ")and(instruccion3[cont+1] == u" ")):
                    primer[1] = cont+1
                    continuar = False
            cont += 1
    while (primer[0]<primer[1]):
        pal += instruccion3[primer[0]]
        primer[0] += 1
    print (pal)
    return pal

y = 0
subprocesado=[]
procesado=[]
instruccion3 = u"INSERT INTO Estudiantes (Nombre,Rut) VALUES ('Fabio Pazos','20227009-3');"
palabra = definir_pal()
if path.exists(palabra+".csv"):
    archivo = open(palabra+".csv","r")
    LECTURA(palabra,archivo)
    print(subprocesado)
    archivo.close()
    INSERT_INTO()
else :
    print ("el archivo no existe\n")
