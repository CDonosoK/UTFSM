from django.db import models


class Maquinas(models.Model):
    tipo_maquina = models.CharField(max_length = 100)
    nombre = models.CharField(max_length = 100)
    ubicacion = models.CharField(max_length = 100)
    def __str__(self):
        return self.tipo_maquina

class Recursos(models.Model):
    tipo_maquina = models.CharField(max_length = 100)
    nombre = models.CharField(max_length = 100)
    url = models.CharField(max_length = 100)

    def __str__(self):
        return self.nombre

class Habilitacion(models.Model):
    rutMaker = models.CharField(max_length=100)
    tipo_maquina=models.CharField(max_length=100)
    habilitado_o_no=models.CharField(max_length=20)
    recursos=models.CharField(max_length=500)

    def __str__(self):
        return str(self.tipo_maquina)
