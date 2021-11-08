from django.urls import path

from .views import maquinas, maquinaBorrar, maquinaAgregar
from .views import recursosBuscar, recursosAgregar, recursosEliminar
from .views import listaHabilitaciones,habilitacionDetail,Search,Si,No,Add, Update

urlpatterns = [
    path('Maquina/All', maquinas),
    path('Maquina/Search', maquinas),
    path('Maquina/Delete/<int:pk>', maquinaBorrar),
    path('Maquina/Add', maquinaAgregar),

    path('Recursos/Search', recursosBuscar),
    path('Recursos/Add', recursosAgregar),
    path('Recursos/Delete/<int:pk>', recursosEliminar),

    path('Habilitacion/', listaHabilitaciones),
    path('Habilitacion/<int:pk>/', habilitacionDetail),
    path('Habilitacion/Si', Si),
    path('Habilitacion/No', No),
    path('Habilitacion/Search',Search),
    path('Habilitacion/Add', Add),
    path('Habilitacion/Update', Update)

]