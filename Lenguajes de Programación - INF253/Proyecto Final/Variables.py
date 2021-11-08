import  pygame
import os

#VARIABLES
Ancho_Sudoku = 600
Alto_Sudoku = 600
Nombre = "-_SUDOKU_-"

#FUNCIONES
def cargarMusica(directorio, tipo = ('.wav', '.mp3')):
    canciones = {}
    for cancion in os.listdir(directorio):
        nombre, extension = os.path.splitext(cancion)
        if extension.lower() in tipo:
            canciones[nombre] = os.path.join(directorio, cancion)
    return canciones

def cargarImagenes(directorio, tipo = ('.png','.jpg')):
    imagenes = {}
    for imagen in os.listdir(directorio):
        nombre, extension = os.path.splitext(imagen)
        if extension.lower() in tipo:
            imagenes[nombre] = pygame.image.load(os.path.join(directorio, imagen))
    return imagenes

#IMAGENES
try:
    IMG = cargarImagenes(os.path.join("Recursos","Imagenes"))
except:
    print("No se encontraron las imagenes")

try:
    MUS = cargarMusica(os.path.join("Recursos","Musica"))
except:
    print("No se encontraron las musicas")

#COLORES
Blanco = (255,255,255)
Negro = (0, 0, 0)
Celeste = (100, 210, 230)
Rojo = (255, 0, 0)
Verde = (0, 255, 0)

#PLANOS


#POSICIONES
posInicial_4 = (75,100)
posInicial_9 = (75,100)
posInicial_16 = (60,80)

tamañoCelda_4 = 50
tamañoCelda_9 = 50
tamañoCelda_16 = 30

tamañoPlano_4 = tamañoCelda_4*4
tamañoPlano_9 = tamañoCelda_9*9
tamañoPlano_16 = tamañoCelda_16*16