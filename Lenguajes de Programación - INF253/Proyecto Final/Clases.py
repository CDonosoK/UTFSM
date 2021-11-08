import pygame

class Cursor(pygame.Rect):
    def __init__(self):
        pygame.Rect.__init__(self,0,0,1,1)
    def Update(self):
        self.left,self.top = pygame.mouse.get_pos()

class Boton(pygame.sprite.Sprite):
    def __init__(self, Imagen1, Imagen2, x = 200, y = 100):
        self.imagen_normal = Imagen1
        self.imagen_seleccionada = Imagen2
        self.imagen_actual = self.imagen_normal
        self.rect = self.imagen_actual.get_rect()
        self.rect.left, self.rect.top = (x,y)

    def Update(self, pantalla, cursor):
        if cursor.colliderect(self.rect):
            self.imagen_actual = self.imagen_seleccionada
        else:
            self.imagen_actual = self.imagen_normal

        pantalla.blit(self.imagen_actual, self.rect)

