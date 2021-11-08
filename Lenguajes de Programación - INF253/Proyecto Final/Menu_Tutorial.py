import pygame
from Clases import Cursor, Boton
from Variables import MUS, IMG

def Menu_Tutorial():
    pygame.init()
    Ancho = 600
    Alto = 600
    FPS = pygame.time.Clock()
    Window = pygame.display.set_mode([Ancho, Alto])
    pygame.display.set_caption("-_Sudoku_-")

    cursor = Cursor()

    pygame.display.set_icon(IMG["Icono"])
    BotonSalir = Boton(IMG["Salir_0"], IMG["Salir_1"], 400, 540)

    Salir = False

    while not Salir:
        FPS.tick(60)

        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                Salir = True
            if evento.type == pygame.MOUSEBUTTONDOWN:
                if cursor.colliderect(BotonSalir.rect):
                    Salir = True

        pygame.display.update()
        cursor.Update()
        Window.blit(IMG["Fondo_Tutorial"],(0,0))
        BotonSalir.Update(Window, cursor)
