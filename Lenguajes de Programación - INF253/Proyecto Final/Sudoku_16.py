import pygame, random, time
from Variables import *
from Clases import Cursor, Boton
from Generador import CrearSudoku, VaciadoAleatorio

class Sudoku_16():
    def __init__(self, dificultad):
        pygame.init()

        pygame.mixer.music.load(MUS["Musica_Juego"])
        pygame.mixer.music.play(100)
        self.ventana = pygame.display.set_mode((Ancho_Sudoku, Alto_Sudoku))
        pygame.display.set_caption(Nombre)

        Ayuda_0 = IMG["Ayuda_0"]
        Ayuda_1 = IMG["Ayuda_1"]
        self.botonAyuda = Boton(pygame.transform.scale(Ayuda_0, (50, 50)), pygame.transform.scale(Ayuda_1, (50, 50)), 110, 25)
        Exit_0 = IMG["Exit_0"]
        Exit_1 = IMG["Exit_1"]
        self.botonSalir = Boton(pygame.transform.scale(Exit_0, (50, 50)), pygame.transform.scale(Exit_1, (50, 50)), 475, 25)
        Solucion_0 = IMG["Solucion_0"]
        Solucion_1 = IMG["Solucion_1"]
        self.botonSolucion = Boton(pygame.transform.scale(Solucion_0, (50, 50)), pygame.transform.scale(Solucion_1, (50, 50)), 50, 25)

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

        self.Dieciseis = True
        self.Dieciseis_listo = 0

        #PLANO 16x16
        self.Solucion_16 = CrearSudoku(16)
        self.Plano16 = VaciadoAleatorio(self.Solucion_16, 16, self.dificultad)
        self.casillasProtegidas16 = []
        self.casillasProbables16 = []
        for fila16 in range(16):
            for columna16 in range(16):
                if self.Plano16[fila16][columna16] != 0:
                    self.casillasProtegidas16.append((columna16, fila16))
                else:
                    self.casillasProbables16.append((columna16, fila16))

    def Jugar(self):
        self.FPS.tick(60)
        while self.jugando:
            self.tiempoJugado = round(time.time() - self.comienzo)

            self.Eventos()
            self.Actualizar()

            if self.Dieciseis:
                if self.CasillasPosibles(self.Plano16, 0):
                    if self.Plano16 == self.Solucion_16:
                        self.Dieciseis_listo = 1
                    else:
                        self.Dieciseis_listo = 2
                    pygame.mixer.music.stop()
                    self.jugando = False

            self.Dibujar()

        if self.Dieciseis_listo == 1:
            pygame.mixer.music.load(MUS["Musica_Ganar"])
            pygame.mixer.music.play()
            time.sleep(7)
        if self.Dieciseis_listo == 2:
            pygame.mixer.music.load(MUS["Musica_Perder"])
            pygame.mixer.music.play()
            time.sleep(5)

    def Eventos(self):
        for evento in pygame.event.get():
            if evento.type == pygame.QUIT:
                self.jugando = False

            if evento.type == pygame.MOUSEBUTTONDOWN:
                if (self.cursor.colliderect(self.botonSolucion.rect)):
                    self.Plano16 = self.Solucion_16

                seleccionada = self.mousePlano()
                if (self.cursor.colliderect(self.botonSalir.rect)):
                    pygame.mixer.music.stop()
                    self.salir = True
                    self.jugando = False

                if (self.cursor.colliderect(self.botonAyuda.rect)) and self.cantida_ayuda!= 1:
                    self.casillaAyuda = random.randint(0, len(self.casillasProbables16)-1)
                    self.cantida_ayuda = len(self.casillasProbables16)
                    self.casillaAyuda = self.casillasProbables16[self.casillaAyuda]
                    self.ayuda = True

                if seleccionada:
                    self.seleccion = [1,2]
                    self.seleccion[0] = seleccionada[0]
                    self.seleccion[1] = seleccionada[1]
                    self.seleccion = (self.seleccion[0], self.seleccion[1])
                    if self.seleccion in self.casillasProtegidas16:
                        self.seleccion = None
                else:
                    self.seleccion = None

            if evento.type == pygame.KEYDOWN:
                self.tecla = pygame.key.name(evento.key)
                if self.tecla == "escape":
                    self.jugando = False

                if self.seleccion:
                    if self.tecla == "return" or self.tecla == "space" or self.tecla == "enter":
                        if self.aux not in ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16']:
                            self.aux = 0
                        self.Plano16[self.seleccion[1]][self.seleccion[0]] = int(self.aux)
                        self.numero = False
                        self.aux = ""

                    if self.tecla in ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16'] or self.tecla in ['[1]','[2]','[3]','[4]','[5]','[6]','[7]','[8]','[9]','[10]','[11]','[12]','[13]','[14]','[15]','[16]']:
                        if self.tecla in ['[1]','[2]','[3]','[4]','[5]','[6]','[7]','[8]','[9]','[10]','[11]','[12]','[13]','[14]','[15]','[16]']:
                            self.tecla = self.tecla[1:-1]
                            self.tecla = int(self.tecla)
                        self.numero = True
                        self.aux = self.tecla
                    else:
                        self.numero = False


    def mousePlano(self):
        if self.posMouse[0] < (posInicial_16[0]) or self.posMouse[1] < (posInicial_16[1] ):
            return False

        if self.posMouse[0] > (posInicial_16[0] + tamañoPlano_16 ) or self.posMouse[1] > (posInicial_16[1] + tamañoPlano_16 ):
            return False

        return ((self.posMouse[0]-posInicial_16[0])//tamañoCelda_16, (self.posMouse[1] - posInicial_16[1])// tamañoCelda_16)

    def Actualizar(self):
        self.posMouse = pygame.mouse.get_pos()
        self.cursor.Update()

    def Dibujar(self):
        self.ventana.blit(IMG["Fondo_Sudoku"], (0,0))
        if self.Dieciseis_listo == 1:
            self.dibujarGanaste(self.ventana)
        if self.Dieciseis_listo == 2:
            self.dibujarPerdiste(self.ventana)

        self.botonAyuda.Update(self.ventana, self.cursor)
        self.botonSolucion.Update(self.ventana, self.cursor)
        self.botonSalir.Update(self.ventana, self.cursor)
        self.segundos = self.tiempoJugado%60
        self.minutos = self.tiempoJugado//60
        self.horas = self.minutos//60
        tiempoTexto = " "+str(self.horas)+" : "+str(self.minutos)+" : "+str(self.segundos)
        self.tiempoTexto = pygame.font.Font('Mario_Bros.TTF', 18).render("TIEMPO JUGADO"+tiempoTexto,1, Negro )
        self.ventana.blit(self.tiempoTexto, (170, 40))


        if self.Dieciseis:
            if self.ayuda:
                self.ayuda = False
                self.casillasProtegidas16.append(self.casillaAyuda)
                self.casillasProbables16.remove((self.casillaAyuda[0], self.casillaAyuda[1]))
                self.Plano16[self.casillaAyuda[1]][self.casillaAyuda[0]] = int(self.Solucion_16[self.casillaAyuda[1]][self.casillaAyuda[0]])

            if self.seleccion:
                self.dibujarSeleccion(self.ventana, self.seleccion, tamañoCelda_16)
            if self.numero and self.seleccion:
                self.texto = pygame.font.Font('Mario_Bros.TTF', 20).render(str(self.tecla), 1, Negro)
                self.ventana.blit(self.texto, (self.seleccion[0]* tamañoCelda_16 + posInicial_16[0] + 6 , self.seleccion[1]*tamañoCelda_16 + posInicial_16[1] + 5))

            self.Dibujar16(self.ventana)
            for fila in range(16):
                for columna in range(16):
                    if self.Plano16[fila][columna] == 0:
                        self.texto = pygame.font.Font('Mario_Bros.TTF', 20).render("", 1, Negro)
                    else:
                        self.texto = pygame.font.Font('Mario_Bros.TTF', 20).render(str(self.Plano16[fila][columna]), 1, Negro)
                    self.ventana.blit(self.texto, (columna * tamañoCelda_16 + posInicial_16[0] + 6, fila * tamañoCelda_16 + posInicial_16[1] + 5))
        pygame.display.update()

    def dibujarSeleccion(self, pantalla, posicion, tamaño):
        pygame.draw.rect(pantalla, Celeste, (((posicion[0])* tamaño) + posInicial_16[0] , ((posicion[1])* tamaño) + posInicial_16[1] , tamaño, tamaño))

    def dibujarGanaste(self, pantalla):
        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("GANASTE", 1, Verde)
        pantalla.blit(self.texto, (180, 0))

    def dibujarPerdiste(self, pantalla):
        self.texto = pygame.font.Font('Mario_Bros.TTF', 40).render("PERDISTE", 1, Rojo)
        pantalla.blit(self.texto, (180, 10))

    def Dibujar16(self, pantalla):
        pygame.draw.rect(pantalla, Negro, (posInicial_16[0], posInicial_16[1], Ancho_Sudoku-120, Alto_Sudoku-120), 3)
        for x in range(16):
            if x % 4 != 0:
                pygame.draw.line(pantalla, Negro, (posInicial_16[0] + (x * tamañoCelda_16 ) ,posInicial_16[1] ), (posInicial_16[0] + (x * tamañoCelda_16 ), posInicial_16[1]+480))
                pygame.draw.line(pantalla, Negro, (posInicial_16[0] , posInicial_16[1] + (x * tamañoCelda_16 )), (posInicial_16[0] + 480, posInicial_16[1] + (x * tamañoCelda_16 )))
            else:
                pygame.draw.line(pantalla, Negro, (posInicial_16[0] + (x * tamañoCelda_16 ) , posInicial_16[1]), (posInicial_16[0] + (x * tamañoCelda_16 ), posInicial_16[1] + 480), 3)
                pygame.draw.line(pantalla, Negro, (posInicial_16[0] , posInicial_16[1] + (x * tamañoCelda_16 )), (posInicial_16[0] + 480, posInicial_16[1] + (x * tamañoCelda_16 ) ), 3)

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