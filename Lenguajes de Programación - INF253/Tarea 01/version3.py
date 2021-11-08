import re

def list_grupos(g):
    if(g.group('ctrl')=='SELECT'):
        return ['cero','uno','dos','tres','cuatro','cinco']
    else:
        return ['cero','uno','dos']

orden = "ON"
validacion = False
columna = "(\w+)"
valor = "(('[a-zA-Z0-9- ]+')|([0-9]+)|([0-9]+\.[0-9]+))"
tabla = "((\w+)|\_)+"

select = re.compile(rf'(?P<ctrl>SELECT ) (?P<cero>({columna} (?: *, *{columna} )*)|\* )FROM (?P<uno>{tabla})(?: INNER JOIN (?P<dos>{tabla}))?(?: WHERE (?P<tres>(?:({columna} = {valor})|({columna} = {columna}))(?: (?:AND|OR) (?:({columna} = {valor})|({columna} = {columna})))*))?(?: ORDER BY (?P<cuatro>{columna}) (?P<cinco>(ASC|DESC)))? ;')
insert = re.compile(rf'(?P<ctrl>INSERT INTO ) (?P<cero>{tabla}) \( (?P<uno>{columna}(?: *, *{columna})*) \) VALUES \( (?P<dos>{valor}(?: *, *{valor})*) \) ;')
update = re.compile(rf'(?P<ctrl>UPDATE ) (?P<cero>{tabla}) SET (?P<uno>{columna} = {valor}(?: *, *{columna} = {valor})*) WHERE (?P<dos>{columna} = {valor} (?:(?:AND {columna} = {valor} |OR {columna} = {valor} ))*);')

patron = [select,insert,update]  

while(orden != "exit"):
    orden=input("Inserte orden o exit para salir: ")
    for px in patron:
        coincidencias=px.finditer(orden)
        for c in coincidencias:
            grupos = list_grupos(c)
            for x in grupos:
                print(c.group(x))      
            validacion = True

    if(not(validacion) and (orden != "exit")):
        print("Error de Sintaxis")
        validacion = False

