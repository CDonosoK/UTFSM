import pygame, random, sys, time
from Variables import *
from Clases import Cursor, Boton
from Generador import CrearSudoku, VaciadoAleatorio

class Sudoku_4():
    def __init__(self, dificultad):
        pygame.init()

        pygame.mixer.music.load(MUS["Musica_Juego"])
        pygame.mixer.music.play(100)
        self.ventana = pygame.display.set_mode((Ancho_Sudoku, Alto_Sudoku))
        pygame.display.set_caption(Nombre)

        Ayuda_0 = IMG["Ayuda_0"]
        Ayuda_1 = IMG["Ayuda_1"]
        self.botonAyuda = Boton(pygame.transform.scale(Ayuda_0, (50, 50)), pygame.transform.scale(Ayuda_1, (50, 50)), 110, 40)
        Exit_0 = IMG["Exit_0"]
        Exit_1 = IMG["Exit_1"]
        self.botonSalir = Boton(pygame.transform.scale(Exit_0, (50, 50)), pygame.transform.scale(Exit_1, (50, 50)), 475, 40)
        Solucion_0 = IMG["Solucion_0"]
        Solucion_1 = IMG["Solucion_1"]
        self.botonSolucion = Boton(pygame.transform.scale(Solucion_0, (50, 50)), pygame.transform.scale(Solucion_1, (50, 50)), 50, 40)
        self.cursor = Cursor()

        self.comienzo = time.time()
        self.vacio = 1
        self.FPS = pygame.time.Clock()

        self.tiempoJugado = 0
        self.aux = 0
        self.texto = ""
        self.ayuda = False
        self.cantida_ayuda = 2
        self.casillaAyuda = (0,0)
        self.salir = False

        self.jugando = True
        self.seleccion = None
        self.posMouse = None
        self.numero = False
        self.dificultad = dificultad

        self.Cuatro = True
        self.Cuatro_listo = 0

        #PLANO 4x4
        self.Solucion_4 = CrearSudoku(4)
        self.Plano4 = VaciadoAleatorio(self.Solucion_4, 4, self.dificultad)
        self.casillasProtegidas4 = []
        self.casillasProbables4 = []
        for fila4 in range(4):
            for columna4 in range(4):
                if self.Plano4[fila4][columna4] != 0:
                    self.casillasProtegidas4.append((columna4, fila4))
                else:
                    self.casillasProbables4.append((columna4, fila4))

    def Jugar(self):
        self.FPS.tick(60)
        while self.jugando:
            self.tiempoJugado = round(time.time() - self.comienzo)

            self.Eventos()
            self.Actualizar()

            if self.Cuatro:
                if self.CasillasPosibles(self.Plano4, 0):
                    if self.Plano4 == self.Solucion_4:
                        self.Cuatro_listo = 1
                    else:
                        self.Cuatro_listo = 2
                    pygame.mixer.music.stop()
                    self.jugando = False
            self.Dibujar()

        if self.Cuatro_listo == 1:
            pygame.mixer.music.load(MUS["Musica_Ganar"])
            pygame.mixer.music.play()
            time.sleep(7)
        if self.Cuatro_listo == 2:
            pygame.mixer.music.load(MUS["Musica_Perder"])
            pygame.mixer.music.play()
            time.sleep(5)

    def Eventos(self):
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                self.jugando = False
                pygame.mixer.music.stop()

            if evento.type == pygame.MOUSEBUTTONDOWN:
                seleccionada = self.mousePlano()
                if (self.cursor.colliderect(self.botonSolucion.rect)):
                    self.Plano4 = self.Solucion_4

                if (self.cursor.colliderect(self.botonSalir.rect)):
                    pygame.mixer.music.stop()
                    self.salir = True
                    self.jugando = False
                    pygame.mixer.music.stop()

                if (self.cursor.colliderect(self.botonAyuda.rect)) and self.cantida_ayuda!= 1:
                    self.casillaAyuda = random.randint(0, len(self.casillasProbables4)-1)
                    self.cantida_ayuda = len(self.casillasProbables4)
                    self.casillaAyuda = self.casillasProbables4[self.casillaAyuda]
                    self.ayuda = True

                if seleccionada:
                    self.seleccion = [1,2]
                    self.seleccion[0] = seleccionada[0] - 3
                    self.seleccion[1] = seleccionada[1] - 1
                    self.seleccion = (self.seleccion[0], self.seleccion[1])
                    if self.seleccion in self.casillasProtegidas4:
                        self.seleccion = None
                else:
                    self.seleccion = None

            if evento.type == pygame.KEYDOWN:
                self.tecla = pygame.key.name(evento.key)
                if self.tecla == "escape":
                    self.jugando = False
                    pygame.mixer.music.stop()

                if self.seleccion:
                    if self.tecla == "return" or self.tecla == "space" or self.tecla == "enter":
                        if self.aux not in ['1','2','3','4']:
                            self.aux = 0
                        self.Plano4[self.seleccion[1]][self.seleccion[0]] = int(self.aux)
                        self.numero = False
                        self.aux = ""

                    if self.tecla in ['1','2','3','4'] or self.tecla in ['[1]','[2]','[3]','[4]']:
                        if self.tecla in ['[1]','[2]','[3]','[4]']:
                            self.tecla = self.tecla[1:-1]
                            self.tecla = int(self.tecla)
                        self.numero = True
                        self.aux = self.tecla
                    else:
                        self.numero = False


    def mousePlano(self):
        if self.posMouse[0] < (posInicial_4[0]+150) or self.posMouse[1] < (posInicial_4[1] + 50):
            return False

        if self.posMouse[0] > (posInicial_4[0] + tamañoPlano_4 + 150) or self.posMouse[1] > (posInicial_4[1] + tamañoPlano_4 + 50):
            return False

        return ((self.posMouse[0]-posInicial_4[0])//tamañoCelda_4, (self.posMouse[1] - posInicial_4[1])// tamañoCelda_4)

    def Actualizar(self):
        self.posMouse = pygame.mouse.get_pos()
        self.cursor.Update()

    def Dibujar(self):
        self.ventana.blit(IMG["Fondo_Sudoku"], (0,0))
        if self.Cuatro_listo == 1:
            self.dibujarGanaste(self.ventana)
        if self.Cuatro_listo == 2:
            self.dibujarPerdiste(self.ventana
                                 )
        self.botonAyuda.Update(self.ventana, self.cursor)
        self.botonSolucion.Update(self.ventana, self.cursor)
        self.botonSalir.Update(self.ventana, self.cursor)
        self.segundos = self.tiempoJugado%60
        self.minutos = self.tiempoJugado//60
        self.horas = self.minutos//60
        tiempoTexto = " "+str(self.horas)+" : "+str(self.minutos)+" : "+str(self.segundos)
        self.tiempoTexto = pygame.font.Font('Mario_Bros.TTF', 18).render("TIEMPO JUGADO"+tiempoTexto,1, Negro )
        self.ventana.blit(self.tiempoTexto, (170, 60))


        if self.Cuatro:
            if self.ayuda:
                self.ayuda = False
                self.casillasProtegidas4.append(self.casillaAyuda)
                self.casillasProbables4.remove((self.casillaAyuda[0], self.casillaAyuda[1]))
                self.Plano4[self.casillaAyuda[1]][self.casillaAyuda[0]] = int(self.Solucion_4[self.casillaAyuda[1]][self.casillaAyuda[0]])

            if self.seleccion:
                self.dibujarSeleccion(self.ventana, self.seleccion, tamañoCelda_9)
            if self.numero and self.seleccion:
                self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render(str(self.tecla), 1, Negro)
                self.ventana.blit(self.texto, (self.seleccion[0]* tamañoCelda_9 + posInicial_4[0] + 165, self.seleccion[1]*tamañoCelda_9 + posInicial_4[1] + 55))

            self.Dibujar4(self.ventana)
            for fila in range(4):
                for columna in range(4):
                    if self.Plano4[fila][columna] == 0:
                        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("", 1, Negro)
                    else:
                        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render(str(self.Plano4[fila][columna]), 1, Negro)
                    self.ventana.blit(self.texto, (columna * tamañoCelda_9 + posInicial_4[0] + 165, fila * tamañoCelda_9 + posInicial_4[1] + 55))
        pygame.display.update()

    def dibujarSeleccion(self, pantalla, posicion, tamaño):
        pygame.draw.rect(pantalla, Celeste, (((posicion[0])* tamaño) + posInicial_4[0] + 150 , ((posicion[1])* tamaño) + posInicial_4[1] + 50, tamaño, tamaño))

    def dibujarGanaste(self, pantalla):
        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("GANASTE", 1, Verde)
        pantalla.blit(self.texto, (200, 10))

    def dibujarPerdiste(self, pantalla):
        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("PERDISTE", 1, Rojo)
        pantalla.blit(self.texto, (200, 10))

    def Dibujar4(self, pantalla):
        pygame.draw.rect(pantalla, Negro, (posInicial_4[0]+150, posInicial_4[1]+50, Ancho_Sudoku-400, Alto_Sudoku-400), 3)
        for x in range(4):
            if x % 2 != 0:
                pygame.draw.line(pantalla, Negro, (posInicial_4[0] + (x * tamañoCelda_4 ) + 150 ,posInicial_4[1] + 50), (posInicial_4[0] + (x * tamañoCelda_4 ) + 150 , posInicial_4[1]+250))
                pygame.draw.line(pantalla, Negro, (posInicial_4[0] + 150, posInicial_4[1] + (x * tamañoCelda_4 ) + 50), (posInicial_4[0] + 350, posInicial_4[1] + (x * tamañoCelda_4 ) + 50))
            else:
                pygame.draw.line(pantalla, Negro, (posInicial_4[0] + (x * tamañoCelda_4 ) + 150, posInicial_4[1] + 50), (posInicial_4[0] + (x * tamañoCelda_4 ) + 150, posInicial_4[1] + 250), 3)
                pygame.draw.line(pantalla, Negro, (posInicial_4[0] + 150, posInicial_4[1] + (x * tamañoCelda_4 ) + 50), (posInicial_4[0] + 350, posInicial_4[1] + (x * tamañoCelda_4 ) + 50), 3)

    def CasillasPosibles(self, plano, contador):
        contador = contador
        for i in plano:
            for j in i:
                if j == 0 or j == '0':
                    contador += 1
        if contador == 0:
            return True
        else:
            return False
