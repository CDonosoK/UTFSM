'''
TAREA 1: Lenguajes de Programación
Clemente Donoso - 201873546-9
Exequiel Perez  - 201873555-8
Entrega: 08 de Septiembre de 2019
'''
import os, re
import sys
sys.stdout.encoding
'UTF-8'
#COMANDOS QUE SE PUEDEN UTILIZAR PARA PROBAR EL PROGRAMA:
comandos = ["SELECT Nombre FROM Estudiantes;",
            "UPDATE Notas SET Nota=54 WHERE Rol='201673557-4';",
            "INSERT INTO Estudiantes (Nombre, Rut) VALUES ('Fabio Pazos', '20227009-3');",
            "INSERT INTO Estudiantes (Nombre, Rut, Rol, Telefono, Edad) VALUES ('Sebastian Godinez', '19991933-8', '201673501-1', 988881234, 21);",
            "UPDATE Notas SET Nota=54 WHERE Rol='201673657-4';",
            "SELECT Telefono FROM Estudiantes WHERE Nombre = 'Clemente Aguilar';"]

'''
verificar
______________________________________
Entradas:
(string) comando: Es el comando ingresado por el usuario
______________________________________
Salida:
(lista) Una lista compuesta de dos listas, donde el primer componente es una variable boleana y el siguiente 
una lista compuesta por los grupos del comando, si el comando está erroneo la salida solo será una lista con
un componente
______________________________________
La función analiza la sintaxis del comando para retornar una lista dependiendo si la sintaxis es correcta o no.
'''
def verificar(comando):
    valores_com = "(([0-9]+)|([0-9]+\.[0-9]+)|'([a-zA-Z0-9- ]+)')"
    valores     = "(([0-9]+)|([0-9]+\.[0-9]+)|([a-zA-Z0-9- ]+)|\*)"

    insert = re.compile(rf'(?P<tipoComando>INSERT INTO )(?P<elemento_0>(\w+)) \((?P<elemento_1>{valores}(?: *, *{valores})*)\) VALUES \((?P<elemento_2>{valores_com}(?: *, *{valores_com})*)\);')
    select = re.compile(rf'(?P<tipoComando>SELECT )(?P<elemento_0>{valores}(?: *, *{valores})*) FROM (?P<elemento_1>{valores})( INNER JOIN (?P<elemento_2>{valores}))?( WHERE (?P<elemento_3>({valores} = {valores_com}( AND|OR {valores} = {valores_com})?)*))?( ORDER BY (?P<elemento_4>{valores}) (?P<elemento_5>(DESC|ASC)))?;')
    update = re.compile(rf'(?P<tipoComando>UPDATE )(?P<elemento_0>{valores}) SET (?P<elemento_1>{valores}={valores}(?: *, *{valores}={valores})*) WHERE (?P<elemento_2>{valores}={valores_com}(?:(?: AND {valores}={valores_com}|OR {valores}={valores_com}))*);')

    sintaxis = [insert, select, update]

    for tipo in sintaxis:
        match = re.search(tipo, comando)
        lista = []
        l_aux = []
        if match:
            #print(match)
            lista.append(True)
            if match.group('tipoComando') == 'INSERT INTO ':
                l_aux.append(match.group('tipoComando'))
                l_aux.append(match.group('elemento_0'))
                l_aux.append(match.group('elemento_1'))
                l_aux.append(match.group('elemento_2'))

            if match.group('tipoComando') == 'SELECT ':
                l_aux.append(match.group('tipoComando'))
                l_aux.append(match.group('elemento_0'))
                l_aux.append(match.group('elemento_1'))
                l_aux.append(match.group('elemento_2'))
                l_aux.append(match.group('elemento_3'))
                l_aux.append(match.group('elemento_4'))
                l_aux.append(match.group('elemento_5'))

            if match.group('tipoComando') == 'UPDATE ':
                l_aux.append(match.group('tipoComando'))
                l_aux.append(match.group('elemento_0'))
                l_aux.append(match.group('elemento_1'))
                l_aux.append(match.group('elemento_2'))
            lista.append(l_aux)
            return lista
    lista.append(False)
    return lista
'''
lectura
______________________________________
Entradas:
(string) archivo: archivo con el que se va a trabajar
______________________________________
Salida:
No tiene salida
______________________________________
Obtiene la información del archivo y luego la guarda en una lista para ser trabajada después.
'''
def lectura(palabra):
    archivo = open(palabra + ".csv", "r")
    for linea in archivo:
        subprocesado.append(linea.strip().split(","))
    y = len(subprocesado[0])
    
    for elem in subprocesado:
        pormientras = []
        for subelem in elem:
            u = subelem #transformacion a utf-8 (puede generar arrores)
            pormientras.append(u)
        procesado.append(pormientras)
    archivo.close()
'''
select
______________________________________
Entradas:
(string) comando: comando ingresado por el usuario
______________________________________
Salida:
No tiene salida
______________________________________
Realiza el comando select con todas sus funcionalidades
'''
def select(comando, lista):
    listaEntrega = []
    condiciones = lista[4]
    queMostrar = lista[1].split(',')
    asterisco = u"*"
    dif = []
    comp = []
    correcto = []
    if u"ORDER BY" in instruccion:
        dif.append(instruccion.split("ORDER BY"))
        instruccion = dif[0][0]
        i = 0
        cont = 0
        for linea in procesado[0]:
            if linea in dif[0][1]:
                cont = i
            i += 1
        print (cont)
        i = 0 
        for linea in procesado:
            if i != 0:
                comp.append(linea[cont])
            i += 1
        comp.sort()
        if u"DESC" in dif [0][1]:
            comp.reverse()
        i = 0
        correcto.append(procesado[0])
        while (i<len(procesado[0])):
            for linea in procesado:
                if comp[i] in linea[cont]:
                    correcto.append(linea)
            i += 1
            print (i)
    else :
        correcto = procesado
    if asterisco in comando:
        cont = []
        for tipo in correcto:
            linea = u""
            for elem in tipo:
                linea = linea+" "+elem
            print(linea)
    else:
        cont = []
        i = 0
        for elem in correcto[0]:
            #print(elem)
            if elem in comando:
                cont.append(i)
            i +=1

        condiciones = condiciones.split(' AND ')
        listaCondiciones = []
        for i in condiciones:
            i = i.split(' OR ')
            for j in i:
                    j = j.split(' = ')
                    listaCondiciones.append(j)

        l_aux = []
        for pedazo in correcto:
            imprimir = u""
            l = []
            for x in cont:
                l.append(pedazo[x])
                imprimir += (u" "+pedazo[x])
            l_aux.append(l)
            listaEntrega.append(imprimir)

        print('CONDICIONES', listaCondiciones)
        print('QUE MOSTRAR ', queMostrar)
        print('AUX ', l_aux)
        listaFinal = []

        for elem in queMostrar:
            l = []
            contar = 0
            for j in l_aux[0]:
                if j != elem:
                    contar += 1
                else:
                    break
            for a in l_aux[1:]:
                l.append(a[contar])
            listaFinal.append(l)
        for dato in listaFinal:
            print(dato)
'''
iner_join (select)
______________________________________
Entradas:
(string) comando: comando ingresado por el usuario
______________________________________
Salida:
No tiene salida
______________________________________
Realiza el comando select con todas sus funcionalidades
'''
def iner_join(instruccion):
    intermedio = instruccion.split(u"WHERE")
    print(intermedio)
    pal = u""
    primer = [-1,-1]
    continuar = True
    cont = 1+intermedio[0].find(u"JOIN")
    lim = len(intermedio[0])
    while continuar:
        if (primer[0]==-1):
            if ((intermedio[0][cont] == u" ")and(intermedio[0][cont+1] != u" ")):
                primer[0] = cont+1
        else :
            if ((intermedio[0][cont] != u" ")and(intermedio[0][cont+1] == u" ")):
                primer[1] = cont+1
                continuar = False
        cont += 1
    while (primer[0]<primer[1]):
        pal += intermedio[0][primer[0]]
        primer[0] += 1
    print (pal) #eliminar
    if path.exists(palabra+".csv"):
        seg_arch = open(pal+u".csv","r")
        otro_sub = []
        otro_pro = []
        for linea in seg_arch:
            otro_sub.append(linea.strip().split(","))
        y = len(otro_sub[0])
    
        for elem in otro_sub:
            pormientras = []
            for subelem in elem:
                u = unicode(subelem,"utf-8")
                pormientras.append(u)
            otro_pro.append(pormientras)
        seg_arch.close()
    else :
        print ("el archivo no existe\n")
    comparacion = u""
    cont = 1+intermedio[1].find(u".")
    cont2 = intermedio[1].find(u" ",cont)
    while cont<cont2:
        comparacion += intermedio[1][cont]
        cont += 1
    if (len(procesado)>0 and len(otro_pro)>0):
        prime = [-1,-1]
        second = [-1,-1]
        i = 0
        for algo in procesado[0]:
            if comparacion in algo:
                prime[0] = i
            if algo in intermedio[0]:
                second[0] = i
            i += 1
        i = 0
        for algo in otro_pro[0]:
            if comparacion in algo:
                prime[1] = i
            if algo in intermedio[0]:
                second[1] = i
            i += 1
        i = 0
        print (prime)
        print (second)
        for linea1 in procesado:
            for linea2 in otro_pro:
                if (linea1[prime[0]]==linea2[prime[1]]):
                    flash = linea1[second[0]]+u" "+linea2[second[1]]
                    print(flash)
    else :
        print("no es posible asignar los rol")
    return
'''
update
______________________________________
Entradas:
(string) comando: comando ingresado por el usuario
______________________________________
Salida:
No tiene salida
______________________________________
Realiza el comando update con todas sus funcionalidades
'''
def update(palabra, comando):
    i = 0 
    j = 0
    igual = u"="
    espacio = u" "
    contenido = []

    for elem in procesado[0]:
        estring = u""
        elem += igual
        if elem in comando:
            n = comando.find(elem)
            m = len(elem)
            o = comando.find(espacio,n)
            i = n+m
            if o==-1:
                while ( i<len(comando) ):
                    estring += comando[i]
                    i += 1
            else :
                while ( i<o ):
                    estring += comando[i]
                    i += 1
            contenido.append([n,m,elem,estring])
    contenido.sort()

    nombreModificar = contenido[0][2][:-1]
    valorModificar = contenido[0][3]
    nombreBuscar = contenido[1][2][:-1]
    valorBuscar = contenido[1][3][1:-2]

    posicionBuscar = 0
    posicionModificar = 0
    for nombreColumna in procesado[0]:
        if nombreColumna == nombreModificar:
            break
        else:
            posicionModificar += 1
    for nombreColumna in procesado[0]:
        if nombreColumna == nombreBuscar:
            break
        else:
            posicionBuscar += 1

    for elem in procesado:
        if elem[posicionBuscar] == valorBuscar:
            elem[posicionModificar] = valorModificar

    archivo = open(palabra + '.csv', "w")

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

    archivo.close()

'''
insert_into
______________________________________
Entradas:
(string) comando: comando ingresado por el usuario
______________________________________
Salida:
No tiene salida
______________________________________
Realiza el comando INSERT INTO con todas sus funcionalidades
'''
def insert_into (palabra, comando):
    p = []
    a = 0
    x = True
    div = comando.split(u"VALUES")
    div[1] = div[1].replace(u')','').replace(u'(','').replace(u';','')
    for elem in procesado[0]:
        if elem in div[0]:
            p.append(a)
        a += 1
    for elem in procesado:
        for j in p:
            if elem[j] in div[1]:
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
            procesado[lim - 1][digito] = ingreso[a]
            procesado[lim - 1][digito] = procesado[lim - 1][digito].replace(u"'", u"")
            while procesado[lim - 1][digito][0] == " ":
                procesado[lim - 1][digito] = procesado[lim - 1][digito].replace(u" ", u"", 1)
            a += 1
    reescritura = open(palabra + ".csv", "w")
    lim = len(procesado[0])
    for linea in procesado:
        i = 0
        for info in linea:
            if (i != (lim - 1)):
                #reescritura.write(info.encode("ASCII", 'ignore'))
                reescritura.write(info)
                reescritura.write(",")
            else:
                reescritura.write(info)
                #reescritura.write(info.encode("ASCII", 'ignore'))
            i += 1
        reescritura.write("\n")
    reescritura.close()


'''
obtenerInformacion
______________________________________
Entradas:
(string) comando: comando ingresado por el usuario
______________________________________
Salida:
(string) pal: nombre del archivo
______________________________________
Obtiene el nombre del archivo con el cual se va a trabajar.
'''
'''def obtenerInformacion(comando):
    se = u"SELECT"
    up = u"UPDATE"
    ii = u"INSERT INTO"
    pal = u""
    primer = [-1,-1]
    continuar = True
    if (se in comando):
        cont = 1+comando.find(u"FROM")
        lim = len(comando)
        while continuar:
            if (primer[0]==-1):
                if ((comando[cont] == u" ")and(comando[cont+1] != u" ")):
                    primer[0] = cont+1
            else :
                if ((comando[cont] != u" ")and(comando[cont+1] == u";")):
                    primer[1] = cont+1
                    continuar = False
            cont += 1
    if (up in comando):
        cont = 6
        while continuar:
            if (primer[0]==-1):
                if ((comando[cont] == u" ")and(comando[cont+1] != u" ")):
                    primer[0] = cont+1
            else :
                if ((comando[cont] != u" ")and(comando[cont+1] == u" ")):
                    primer[1] = cont+1
                    continuar = False
            cont += 1
    if (ii in comando):
        cont = 11
        while continuar:
            if (primer[0]==-1):
                if ((comando[cont] == u" ")and(comando[cont+1] != u" ")):
                    primer[0] = cont+1
            else :
                if ((comando[cont] != u" ")and(comando[cont+1] == u" ")):
                    primer[1] = cont+1
                    continuar = False
            cont += 1
    while (primer[0]<primer[1]):
        pal += comando[primer[0]]
        primer[0] += 1
    #print (pal)
    return pal'''

def main():
    exit = False
    while not exit:
        comando = input("Ingrese el comando, [2]Si desea salir: ")
        if comando == '2':
            print('SALIR')
            exit = True
        else:
            sintaxisComando = verificar(comando)
            if sintaxisComando[0]:
                #procesado de la informacion
                tipoComando = sintaxisComando[1][0]
                palabra = sintaxisComando[1][2]
                if os.path.exists(palabra+".csv"):
                    lectura(palabra)
                    if tipoComando == u'UPDATE ':
                        update(palabra, comando)
                    elif tipoComando == u'INSERT INTO ':
                        insert_into(palabra, comando)
                    elif tipoComando == u'SELECT ':
                        if "INNER JOIN" in comando:
                            iner_join(comando)
                        else :
                            select(comando, sintaxisComando[1])
                else:
                    print('Error, el nombre del archivo no existe')
            else:
                print('Error de sintaxis!')

if __name__ == '__main__':
    global procesado, subprocesado, y
    y = 0
    procesado = []
    subprocesado = []
    main()
