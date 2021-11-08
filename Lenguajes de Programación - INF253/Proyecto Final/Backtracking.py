import copy

'''
t_4 =[
    [3,4,1,0],
    [0,2,0,0],
    [0,0,2,0],
    [0,1,4,3]
]

t_9 =[
    [5,3,0,0,7,0,0,0,0],
    [6,0,0,1,9,5,0,0,0],
    [0,9,8,0,0,0,0,6,0],
    [8,0,0,0,6,0,0,0,3],
    [4,0,0,8,0,3,0,0,1],
    [7,0,0,0,2,0,0,0,6],
    [0,6,0,0,0,0,2,8,0],
    [0,0,0,4,1,9,0,0,5],
    [0,0,0,0,8,0,0,7,9]
]

t_92 = [
        [0, 0, 0, 0, 0, 6, 0, 0, 5],
        [0, 0, 7, 0, 0, 0, 0, 0, 3],
        [0, 0, 8, 1, 0, 0, 0, 0, 0],
        [0, 4, 0, 0, 0, 9, 3, 0, 7],
        [1, 0, 0, 2, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 4, 0],
        [0, 0, 1, 0, 0, 0, 0, 0, 0],
        [0, 0, 5, 8, 0, 0, 0, 7, 0],
        [0, 2, 0, 9, 0, 0, 6, 0, 0]]

t_16=[
    [0,6,0,0,0,0,0,8,11,0,0,15,14,0,0,16],
    [15,11,0,0,0,16,14,0,0,0,12,0,0,6,0,0],
    [13,0,9,12,0,0,0,0,3,16,14,0,15,11,10,0],
    [2,0,16,0,11,0,15,10,1,0,0,0,0,0,0,0],
    [0,15,11,10,0,0,16,2,13,8,9,12,0,0,0,0],
    [12,13,0,0,4,1,5,6,2,3,0,0,0,0,11,10],
    [5,0,6,1,12,0,9,0,15,11,10,7,16,0,0,3],
    [0,2,0,0,0,10,0,11,6,0,5,0,0,13,0,9],
    [10,7,15,11,16,0,0,0,12,13,0,0,0,0,0,6],
    [9,0,0,0,0,0,1,0,0,2,0,16,10,0,0,11],
    [1,0,4,6,9,13,0,0,7,0,11,0,3,16,0,0],
    [16,14,0,0,7,0,10,15,4,6,1,0,0,0,13,8],
    [11,10,0,15,0,0,0,16,9,12,13,0,0,1,5,4],
    [0,0,12,0,1,4,6,0,16,0,0,0,11,10,0,0],
    [0,0,5,0,8,12,13,0,10,0,0,11,2,0,0,14],
    [3,16,0,0,10,0,0,7,0,0,6,0,0,0,12,0]
]
'''


def backtrack(sudoku):
    
    pos=sitioVacio(sudoku)
    if not pos:
        return True,sudoku
    for valor in range(1,(len(sudoku)+1)):
        if validar(sudoku,pos,valor):
            sudoku[pos[0]][pos[1]] = valor

            if backtrack(sudoku):
                return True,sudoku
            sudoku[pos[0]][pos[1]] = 0

    return False

def sitioVacio(sudoku):
    for fila in range(len(sudoku)):
        for columna in range(len(sudoku)):
            if sudoku[fila][columna] == 0:
                return (fila,columna)
    return False
        
def validar(sudoku,pos,num):

    for x in range(len(sudoku)):
        if sudoku[pos[0]][x] == num and pos[1] != x:
            return False
    
    for x in range(len(sudoku)):
        if sudoku[x][pos[1]] == num and pos[0] != x:
            return False

    if len(sudoku) == 16:
        aux=4
    elif len(sudoku) == 9:
        aux=3
    else:
        aux=2

    cuadrante_f = pos[0] //aux
    cuadrante_c = pos[1] //aux

    for fila in range(cuadrante_f*aux,cuadrante_f*aux +aux):
        for columna in range(cuadrante_c*aux,cuadrante_c*aux +aux):
            if sudoku[fila][columna] == num and (fila,columna) != pos:
                return False

    return True



def printSudoku(sudoku):
    if len(sudoku) == 4:
        div = 2
    elif len(sudoku) == 9:
        div = 3
    else:
        div = 4

    for x in range(len(sudoku)):
        if x % div == 0 and x != 0:
            print("- "*len(sudoku) +"- "*(div-1))

        for y in range(len(sudoku[0])):
            if y % div == 0 and y != 0:
                print("| ", end="")
            if y == (len(sudoku)-1):
                print(sudoku[x][y])
            else:
                print(str(sudoku[x][y]) + " ", end="")

#backtrack(t_9)
#printSudoku(t_9)