import pygame
from Clases import Cursor, Boton
from Menu_Opciones import Menu_Opciones
from Menu_Tutorial import Menu_Tutorial
from Variables import MUS, IMG

def Main_Menu():
    pygame.init()
    Ancho = 600
    Alto = 600
    FPS = pygame.time.Clock()
    Window = pygame.display.set_mode([Ancho, Alto])
    pygame.display.set_caption("-_Sudoku_-")

    cursor = Cursor()
    pygame.mixer.music.load(MUS["Musica_Menu"])
    pygame.mixer.music.play(10)

    pygame.display.set_icon(IMG["Icono"])
    BotonStart = Boton(IMG["Start_0"], IMG["Start_1"],380,280)
    BotonTutorial = Boton(IMG["Tutorial_0"], IMG["Tutorial_1"], 380, 330)
    BotonSalir = Boton(IMG["Salir_0"], IMG["Salir_1"], 380, 380)

    Salir = False

    while not Salir:
        FPS.tick(60)

        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                Salir = True
            if evento.type == pygame.MOUSEBUTTONDOWN:
                if cursor.colliderect(BotonSalir.rect):
                    Salir = True

                if cursor.colliderect(BotonStart.rect):
                    Menu_Opciones()

                if cursor.colliderect(BotonTutorial.rect):
                    Menu_Tutorial()


        pygame.display.update()
        cursor.Update()
        Window.blit(IMG["Fondo_Main"],(0,0))
        BotonStart.Update(Window,cursor)
        BotonTutorial.Update(Window, cursor)
        BotonSalir.Update(Window, cursor)
    pygame.quit()
