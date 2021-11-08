import pygame
from Clases import Cursor, Boton
from Sudoku_4 import Sudoku_4
from Sudoku_9 import Sudoku_9
from Sudoku_16 import Sudoku_16

from Variables import MUS, IMG

def Menu_Opciones():
    pygame.init()

    Ancho = 600
    Alto = 600
    FPS = pygame.time.Clock()
    Window = pygame.display.set_mode([Ancho, Alto])
    pygame.display.set_caption("-_Sudoku_-")

    cursor = Cursor()

    pygame.display.set_icon(IMG["Icono"])
    BotonSalir = Boton(IMG["Salir_0"],IMG["Salir_1"], 205, 450)

    BotonS4 = Boton(IMG["4x4_0"], IMG["4x4_1"],30,200)
    BotonS9 = Boton(IMG["9x9_0"], IMG["9x9_1"], 30, 270)
    BotonS16 = Boton(IMG["16x16_0"], IMG["16x16_1"], 30, 340)

    BotonFacil = Boton(IMG["Facil_0"], IMG["Facil_1"], 440, 200)
    BotonMedio = Boton(IMG["Medio_0"], IMG["Medio_1"], 440, 270)
    BotonDificil = Boton(IMG["Dificil_0"], IMG["Dificil_1"], 440, 340)

    Salir = False
    Dificultad = None
    Tipo = None

    while not Salir:
        FPS.tick(60)

        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                Salir = True
            if evento.type == pygame.MOUSEBUTTONDOWN:
                if cursor.colliderect(BotonSalir.rect):
                    Salir = True

                if cursor.colliderect(BotonS4.rect):
                    Tipo = 4
                if cursor.colliderect(BotonS9.rect):
                    Tipo = 9
                if cursor.colliderect(BotonS16.rect):
                    Tipo = 16

                if cursor.colliderect(BotonFacil.rect):
                    Dificultad = 1
                if cursor.colliderect(BotonMedio.rect):
                    Dificultad = 2
                if cursor.colliderect(BotonDificil.rect):
                    Dificultad = 3

        if Tipo != None and Dificultad != None:
            if Tipo == 4:
                Sudoku = Sudoku_4(Dificultad)
            if Tipo == 9:
                Sudoku = Sudoku_9(Dificultad)
            if Tipo == 16:
                Sudoku = Sudoku_16(Dificultad)

            Sudoku.Jugar()
            pygame.mixer.music.load(MUS["Musica_Menu"])
            pygame.mixer.music.play(10)
            Tipo = None
            Dificultad = None

        pygame.display.update()
        cursor.Update()
        Window.blit(IMG["Fondo_Menu"],(0,0))
        BotonSalir.Update(Window, cursor)

        BotonS4.Update(Window,cursor)
        BotonS9.Update(Window, cursor)
        BotonS16.Update(Window, cursor)

        BotonFacil.Update(Window, cursor)
        BotonMedio.Update(Window, cursor)
        BotonDificil.Update(Window, cursor)
