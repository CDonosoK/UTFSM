import Backtracking as Back
import random as ran
import copy
import time


def CrearSudoku(n,s):
    if (n == 4):
        disponibles = [1,2,3,4]
        limiteT=0.8
    elif (n == 9):
        disponibles = [1,2,3,4,5,6,7,8,9]
        limiteT=1
    elif (n == 16):
        disponibles = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
        limiteT=0.55
    
    v = False
    aux=n-1
    while not v :
        sudo=copy.deepcopy(s)

        if (n == 9):
            t = ran.randint(17, 46)
        elif (n == 16):
            t = 42#ran.randint(33,121)
        else:
            t = ran.randint(4, 8)
        

        while t != 0:
            i = ran.randint(0,aux)
            il = ran.randint(0,aux)
            ic = ran.randint(0,aux)
            pos = (il,ic)
            if (sudo[il][ic] == 0 and Back.validar(sudo, pos, disponibles[i])):
                sudo[il][ic] = disponibles[i]
                t-=1

        retorno = copy.deepcopy(sudo)

        start_time = time.time()
        v = Back.backtrack(sudo,start_time,limiteT)
    
    return retorno,v[1]
    
    
def CrearSudokuVacio(n):
    s=[]
    for x in range(n):
        s.append([])
        for y in range(n):
            s[x].append(0)
    return s


##############
#CAMBIAR NUMERO POR 4,9 O 16, PROPUESTA ES EL SUDOKU GENERADOR Y SOLUCION SU SOLUCION OBVIAMENTE XD
propuesta,solucion=CrearSudoku(9,CrearSudokuVacio(9))

##############

'''
Back.printSudoku(propuesta)
print("==========================================")
Back.printSudoku(solucion)
tf=time()-ti
print("F tardo: %.10f segundos." %tf)
'''
