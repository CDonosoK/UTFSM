import pygame, random, sys, time
from Variables import *
from Clases import Cursor, Boton
from Generador import CrearSudoku, VaciadoAleatorio

class Sudoku_9():
    def __init__(self, dificultad):
        pygame.init()

        pygame.mixer.music.load(MUS["Musica_Juego"])
        pygame.mixer.music.play(100)
        self.ventana = pygame.display.set_mode((Ancho_Sudoku, Alto_Sudoku))
        pygame.display.set_caption(Nombre)

        Ayuda_0 = IMG["Ayuda_0"]
        Ayuda_1 = IMG["Ayuda_1"]
        self.botonAyuda = Boton(pygame.transform.scale(Ayuda_0, (50, 50)), pygame.transform.scale(Ayuda_1, (50, 50)),
                                110, 40)
        Exit_0 = IMG["Exit_0"]
        Exit_1 = IMG["Exit_1"]
        self.botonSalir = Boton(pygame.transform.scale(Exit_0, (50, 50)), pygame.transform.scale(Exit_1, (50, 50)), 475,
                                40)
        Solucion_0 = IMG["Solucion_0"]
        Solucion_1 = IMG["Solucion_1"]
        self.botonSolucion = Boton(pygame.transform.scale(Solucion_0, (50, 50)),
                                   pygame.transform.scale(Solucion_1, (50, 50)), 50, 40)
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

        self.Nueve = True
        self.Nueve_listo = 0

        #PLANO 9x9
        self.Solucion_9 = CrearSudoku(9)
        self.Plano9 = VaciadoAleatorio(self.Solucion_9, 9, self.dificultad)
        self.casillasProtegidas9 = []
        self.casillasProbables9 = []
        for fila9 in range(9):
            for columna9 in range(9):
                if self.Plano9[fila9][columna9] != 0:
                    self.casillasProtegidas9.append((columna9, fila9))
                else:
                    self.casillasProbables9.append((columna9, fila9))

    def Jugar(self):
        self.FPS.tick(60)
        while self.jugando:
            self.tiempoJugado = round(time.time() - self.comienzo)

            self.Eventos()
            self.Actualizar()
            if self.Nueve:
                if self.CasillasPosibles(self.Plano9, 0):
                    if self.Plano9 == self.Solucion_9:
                        self.Nueve_listo = 1
                    else:
                        self.Nueve_listo = 2
                    pygame.mixer.music.stop()
                    self.jugando = False
            self.Dibujar()

        if self.Nueve_listo == 1:
            pygame.mixer.music.load(MUS["Musica_Ganar"])
            pygame.mixer.music.play()
            time.sleep(7)
        if self.Nueve_listo == 2:
            pygame.mixer.music.load(MUS["Musica_Perder"])
            pygame.mixer.music.play()
            time.sleep(5)

    def Eventos(self):
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                self.jugando = False

            if evento.type == pygame.MOUSEBUTTONDOWN:
                seleccionada = self.mousePlano()
                if (self.cursor.colliderect(self.botonSolucion.rect)):
                    self.Plano9 = self.Solucion_9

                if (self.cursor.colliderect(self.botonSalir.rect)):
                    pygame.mixer.music.stop()
                    self.salir = True
                    self.jugando = False

                if (self.cursor.colliderect(self.botonAyuda.rect)) and self.cantida_ayuda!= 1:
                    self.casillaAyuda = random.randint(0, len(self.casillasProbables9)-1)
                    self.cantida_ayuda = len(self.casillasProbables9)
                    self.casillaAyuda = self.casillasProbables9[self.casillaAyuda]
                    self.ayuda = True

                if seleccionada:
                    self.seleccion = seleccionada
                    if self.seleccion in self.casillasProtegidas9:
                        self.seleccion = None
                else:
                    self.seleccion = None

            if evento.type == pygame.KEYDOWN:
                self.tecla = pygame.key.name(evento.key)
                if self.tecla == "escape":
                    self.jugando = False

                if self.seleccion:
                    if self.tecla == "return" or self.tecla == "space" or self.tecla == "enter":
                        if self.aux not in ['1','2','3','4','5','6','7','8','9']:
                            self.aux = 0
                        self.Plano9[self.seleccion[1]][self.seleccion[0]] = int(self.aux)
                        self.numero = False
                        self.aux = ""

                    if self.tecla in ['1','2','3','4','5','6','7','8','9'] or self.tecla in ['[1]','[2]','[3]','[4]','[5]','[6]','[7]','[8]','[9]']:
                        if self.tecla in ['[1]','[2]','[3]','[4]','[5]','[6]','[7]','[8]','[9]']:
                            self.tecla = self.tecla[1:-1]
                            self.tecla = int(self.tecla)
                        self.numero = True
                        self.aux = self.tecla
                    else:
                        self.numero = False


    def mousePlano(self):
        if self.posMouse[0] < posInicial_9[0] or self.posMouse[1] < posInicial_9[1]:
            return False

        if self.posMouse[0] > posInicial_9[0] + tamañoPlano_9 or self.posMouse[1] > posInicial_9[1] + tamañoPlano_9:
            return False

        return ((self.posMouse[0]-posInicial_9[0])//tamañoCelda_9, (self.posMouse[1] - posInicial_9[1])// tamañoCelda_9)

    def Actualizar(self):
        self.posMouse = pygame.mouse.get_pos()
        self.cursor.Update()

    def Dibujar(self):
        self.ventana.blit(IMG["Fondo_Sudoku"], (0,0))
        if self.Nueve_listo == 1:
            self.dibujarGanaste(self.ventana)
        if self.Nueve_listo == 2:
            self.dibujarPerdiste(self.ventana)

        self.botonAyuda.Update(self.ventana, self.cursor)
        self.botonSolucion.Update(self.ventana, self.cursor)
        self.botonSalir.Update(self.ventana, self.cursor)
        self.segundos = self.tiempoJugado%60
        self.minutos = self.tiempoJugado//60
        self.horas = self.minutos//60
        tiempoTexto = " "+str(self.horas)+" : "+str(self.minutos)+" : "+str(self.segundos)
        self.tiempoTexto = pygame.font.Font('Mario_Bros.TTF', 18).render("TIEMPO JUGADO"+tiempoTexto,1, Negro )
        self.ventana.blit(self.tiempoTexto, (170, 60))

        if self.Nueve:
            if self.ayuda:
                self.ayuda = False
                self.casillasProtegidas9.append(self.casillaAyuda)
                self.casillasProbables9.remove((self.casillaAyuda[0], self.casillaAyuda[1]))
                self.Plano9[self.casillaAyuda[1]][self.casillaAyuda[0]] = int(self.Solucion_9[self.casillaAyuda[1]][self.casillaAyuda[0]])

            if self.seleccion:
                self.dibujarSeleccion(self.ventana, self.seleccion, tamañoCelda_9)
            if self.numero and self.seleccion:
                self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render(str(self.tecla), 1, Negro)

                self.ventana.blit(self.texto, (self.seleccion[0]* tamañoCelda_9 + posInicial_9[0] + 15, self.seleccion[1]*tamañoCelda_9 + posInicial_9[1] + 5))
            self.Dibujar9(self.ventana)
            for fila in range(9):
                for columna in range(9):
                    if self.Plano9[fila][columna] == 0:
                        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("", 1, Negro)
                    else:
                        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render(str(self.Plano9[fila][columna]), 1, Negro)
                    self.ventana.blit(self.texto, (columna * tamañoCelda_9 + posInicial_9[0] + 15, fila * tamañoCelda_9 + posInicial_9[1] + 5))


        pygame.display.update()
    def dibujarSeleccion(self, pantalla, posicion, tamaño):
        pygame.draw.rect(pantalla, Celeste, ((posicion[0] * tamaño) + posInicial_9[0], (posicion[1]* tamaño) + posInicial_9[1], tamaño, tamaño))

    def dibujarGanaste(self, pantalla):
        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("GANASTE", 1, Verde)
        pantalla.blit(self.texto, (200, 10))

    def dibujarPerdiste(self, pantalla):
        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("PERDISTE", 1, Rojo)
        pantalla.blit(self.texto, (200, 10))

    def Dibujar9(self, pantalla):
        pygame.draw.rect(pantalla, Negro, (posInicial_9[0], posInicial_9[1], Ancho_Sudoku-150, Alto_Sudoku-150), 3)
        for x in range(9):
            if x % 3 != 0:
                pygame.draw.line(pantalla, Negro, (posInicial_9[0]+(x * tamañoCelda_9 ),posInicial_9[1]), (posInicial_9[0] + (x * tamañoCelda_9 ), posInicial_9[1]+450))
                pygame.draw.line(pantalla, Negro, (posInicial_9[0], posInicial_9[1] + (x * tamañoCelda_9 )), (posInicial_9[0] + 450, posInicial_9[1] + (x * tamañoCelda_9 )))
            else:
                pygame.draw.line(pantalla, Negro, (posInicial_9[0] + (x * tamañoCelda_9 ), posInicial_9[1]), (posInicial_9[0] + (x * tamañoCelda_9 ), posInicial_9[1] + 450), 3)
                pygame.draw.line(pantalla, Negro, (posInicial_9[0], posInicial_9[1] + (x * tamañoCelda_9 )), (posInicial_9[0] + 450, posInicial_9[1] + (x * tamañoCelda_9 )), 3)

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