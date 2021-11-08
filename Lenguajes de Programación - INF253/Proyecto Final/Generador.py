import math
import Backtracking as Back
import random as ran
import copy

def CrearSudoku(n):
	sudo = CrearSudoInicial(n)
	l=[1,2,3]


	ran.shuffle(l)

	while len(l) > 0:
		opc = l.pop()
		repetir = ran.randint(1,n)
		if opc == 1:
			while repetir > 0:
				sudo = PermutacionSubMatrices(sudo,n)
				sudo = PermutacionColumnas(sudo,n)
				repetir-=1
		elif opc == 2:
			while repetir > 0:
				sudo = PermutacionFilas(sudo, n)
				sudo = PermutacionColumnas(sudo,n)
				repetir-=1
		else:
			while repetir > 0:
				sudo = PermutacionColumnas(sudo,n)
				sudo = PermutacionFilas(sudo, n)
				repetir-=1
	return sudo

def CrearSudoInicial(n):
	sudo=[]
	raiz=int(math.sqrt(n))
	for x in range(1,raiz+1):
		l=[x]
		for aux in range(x+1,x+n):
			if(aux!=n):
				l.append(aux%n)    
			else:        
				l.append(n)
		sudo.append(l.copy())

		for y in range(raiz-1):
			pos=(x-1)*raiz
			l=((sudo[pos+y]).copy())[raiz:n] + ((sudo[pos+y]).copy())[:raiz]
            
			sudo.append(l)
    
	return sudo
def PermutacionColumnas(sudo, n):
	r = int(math.sqrt(n))
	v = ran.randint(r, n+2)
	aux = 0
	while v != 0:
		a = ran.randint(0, n-1)
		b = ran.randint(0, n-1)
		if a != b:
			cor_a = a//r
			cor_b = b//r
			if (cor_a == cor_b):
				for x in range(n):
					aux = sudo[x][a]
					sudo[x][a]=sudo[x][b]
					sudo[x][b]=aux
				v -= 1
	return sudo

def PermutacionFilas(sudo, n):
	r = int(math.sqrt(n))
	v = ran.randint(r, n+2)
	aux = []
	while v != 0:
		a = ran.randint(0, n-1)
		b = ran.randint(0, n-1)
		if a != b:
			cor_a = a//r
			cor_b = b//r
			if (cor_a == cor_b):
				aux = sudo[a]
				sudo[a] = sudo[b]
				sudo[b] = aux
				v -= 1
	return sudo

def PermutacionSubMatrices(sudo,n):
	r = int(math.sqrt(n))
	v = ran.randint(r, n+2)
	while v != 0:
		aux=[]
		a = ran.randint(0, r-1)
		b = ran.randint(0, r-1)
		if a != b:
			for x in range(r):
				aux=sudo[a*r+x]
				sudo[a*r+x]=sudo[b*r+x]
				sudo[b*r+x]=aux
			v-=1
	return sudo

def VaciadoAleatorio(sudo,n,dificultad=2):
    posiciones=[] # posiciones disponibles
    sudoku=copy.deepcopy(sudo)

    for x in range(n):
        for y in range(n):
            posiciones.append((x,y))
    if dificultad == 0: #Facil 
        if n == 4:
            eliminar = ran.randint(4,6)
        elif n == 9:
            eliminar = ran.randint(35,40)
        else:
            eliminar = ran.randint(115,125)
    elif dificultad == 2: #Medio
        if n == 4:
            eliminar = ran.randint(7,9)
        elif n == 9:
            eliminar = ran.randint(41,49)
        else:
            eliminar = ran.randint(126,140)
    else: #Dificil
        if n == 4:
            eliminar = ran.randint(10,12)
        elif n == 9:
            eliminar = ran.randint(50,60)
        else:
            eliminar = ran.randint(141,180)

    while eliminar != 0:
        x,y=ran.choice(posiciones)
        sudoku[x][y]=0
        posiciones.remove((x,y))
        eliminar -=1
    return sudoku

#sudoku = CrearSudoku(16)
#vaciado = VaciadoAleatorio(sudoku,16)
# PARA ESPECIFICAR DIFICULTAD AGREGAR UN VALOR 1,2 O 3, POR DEFECTO TRAE 2 (1=FACIL,2=MEDIO,3=DIFICIL)
#b= Back.backtrack(copy.deepcopy(vaciado))
