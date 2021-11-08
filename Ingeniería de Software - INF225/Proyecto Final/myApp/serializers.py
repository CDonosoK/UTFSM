from rest_framework import serializers
from .models import Maquinas, Recursos


class MaquinasSerializer(serializers.ModelSerializer):
    class Meta:
        model = Maquinas
        fields = ['id', 'tipo_maquina', 'nombre', 'ubicacion'] 

class RecursosSerializer(serializers.ModelSerializer):
    class Meta:
        model = Recursos
        fields = ['id', 'tipo_maquina', 'nombre', 'url']      

from .models import Habilitacion
class HabilitacionesSerializer(serializers.ModelSerializer):
    class Meta:
        model = Habilitacion
        fields = ['id','rutMaker','tipo_maquina','habilitado_o_no','recursos']             


    