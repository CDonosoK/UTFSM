from django.contrib import admin

from .models import Maquinas, Recursos, Habilitacion

admin.site.register(Maquinas)
admin.site.register(Recursos)
admin.site.register(Habilitacion)