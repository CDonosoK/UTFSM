import requests

from django.shortcuts import render
from django.http import HttpResponse, JsonResponse, request
from rest_framework import serializers
from rest_framework.parsers import JSONParser

from .models import Maquinas, Recursos, Habilitacion

from .serializers import MaquinasSerializer, RecursosSerializer, HabilitacionesSerializer
from django.views.decorators.csrf import csrf_exempt

@csrf_exempt
def maquinas(req):
    if req.method == 'GET':
        maquinas = req.GET.get('tipo_maquina')
        listaMaquinas = {}
        
        try:
            maquinasT = Maquinas.objects.filter(tipo_maquina__icontains=maquinas)
            maquinas_S =MaquinasSerializer(maquinasT, many = True)
            for elemento in maquinas_S.data:
                maquina = {}

                reservaMaquina = False
                maquina['tipo_maquina'] = elemento['tipo_maquina']
                maquina['nombre'] = elemento['nombre']
                maquina['ubicacion'] = elemento['ubicacion']
                listaReservas = requests.get("https://api-gestion-25.herokuapp.com/reservas")
                for j in listaReservas.json():
                    if j['id_maquina']==elemento['id']:
                        reservaMaquina = True

                if reservaMaquina:
                    maquina['reservado'] = 'está reservado'
                    listaMaquinas[elemento['id']] = maquina
                else:
                    maquina['reservado'] = 'no está reservado'
                    listaMaquinas[elemento['id']] = maquina
                


            return JsonResponse(listaMaquinas, safe = False)
        except Maquinas.DoesNotExist:
            return HttpResponse(status = 404)

@csrf_exempt
def maquinaAgregar(req):
    if req.method == 'POST':
        nData = {
            'tipo_maquina':req.GET.get('tipo_maquina'),
            'nombre':req.GET.get('nombre'),
            'ubicacion':req.GET.get('ubicacion')
        }
        serializerData = MaquinasSerializer(data = nData)
        print(serializerData)
        if serializerData.is_valid():
            serializerData.save()
            return JsonResponse(serializerData.data, status=201)
        return JsonResponse(serializerData.errors, status = 400)

@csrf_exempt
def maquinaBorrar(req, pk):
    try:
        maquina = Maquinas.objects.get(pk=pk)
    
    except Maquinas.DoesNotExist:
        return HttpResponse(status = 404)

    if req.method == 'DELETE':
        maquina.delete()
        return HttpResponse(status = 204)

@csrf_exempt
def recursosBuscar(req):
    if req.method == 'GET':
        recursos = req.GET.get('tipo_maquina')
        try:
            recursosT = Recursos.objects.filter(tipo_maquina__icontains=recursos)
            recursos_S =RecursosSerializer(recursosT, many = True)
            return JsonResponse(recursos_S.data, safe = False)
        except Recursos.DoesNotExist:
            return HttpResponse(status = 404)

@csrf_exempt
def recursosAgregar(req):
    if req.method == 'POST':
        nData = {
            'tipo_maquina':req.GET.get('tipo_maquina'),
            'nombre':req.GET.get('nombre'),
            'url':req.GET.get('url')
        }

        serializerData = RecursosSerializer(data = nData)
        if serializerData.is_valid():
            serializerData.save()
            return JsonResponse(serializerData.data, status=201)
        return JsonResponse(serializerData.errors, status = 400)


@csrf_exempt
def recursosEliminar(req, pk):
    try:
        recurso = Recursos.objects.get(pk=pk)
        
    except Recursos.DoesNotExist:
        return HttpResponse(status = 404)

    if req.method == 'DELETE':
        recurso.delete()
        return HttpResponse(status = 204)

@csrf_exempt
def listaHabilitaciones(req):
    if req.method == 'GET':
        
        listaHabilitaciones = Habilitacion.objects.all()
        listaHabilitaciones_S = HabilitacionesSerializer(listaHabilitaciones, many = True)

        listaHabilitados = {}
        for elemento in listaHabilitaciones_S.data:
            habilitacion = {}
            habilitacion['rutMaker'] = elemento['rutMaker']
            habilitacion['tipo_maquina'] = elemento['tipo_maquina']
            habilitacion['habilitado_o_no'] = elemento['habilitado_o_no']
            habilitacion['recursos'] = elemento['recursos']

            listaReservas = requests.get("http://ec2-18-188-125-103.us-east-2.compute.amazonaws.com:5000/maker")

            estudiantes = listaReservas.json()["data"]["Estudiantes"]
            rutBuscar = elemento['rutMaker']
            idBuscado = None
            nombre = ""
            for i in estudiantes.get("rut"):
                if estudiantes.get("rut")[i] == rutBuscar:
                    idBuscado = i

            if idBuscado == None:
                nombre = " - "
            else:
                for i in estudiantes.get("nombre"):
                    if i == idBuscado:
                        nombre = estudiantes.get("nombre")[i]
        
            habilitacion['nombre'] = nombre
            listaHabilitados[elemento['id']] = habilitacion
        
        return JsonResponse(listaHabilitados, safe = False)   

@csrf_exempt
def habilitacionDetail(req, pk):
    try:
        habilitacion = Habilitacion.objects.get(pk=pk)
        
    
    except Habilitacion.DoesNotExist:
        return HttpResponse(status = 404)

    if req.method == 'GET':
        habilitacion_S = HabilitacionesSerializer(habilitacion)
        return JsonResponse(habilitacion_S.data)

    elif req.method == 'DELETE':
        habilitacion.delete()
        return HttpResponse(status = 204)

@csrf_exempt
def Search(req):
    if req.method == 'GET':
        id=req.GET.get('rutMaker')
        tipo=req.GET.get('tipo_maquina')
        search = Habilitacion.objects.filter(rutMaker=id).filter(tipo_maquina=tipo)
        search_S = HabilitacionesSerializer(search,many = True, context={'request': req})
        
        listaHabilitados = {}
        for elemento in search_S.data:
            habilitacion = {}
            habilitacion['rutMaker'] = elemento['rutMaker']
            habilitacion['tipo_maquina'] = elemento['tipo_maquina']
            habilitacion['habilitado_o_no'] = elemento['habilitado_o_no']
            habilitacion['recursos'] = elemento['recursos']

            listaReservas = requests.get("http://ec2-18-188-125-103.us-east-2.compute.amazonaws.com:5000/maker")

            estudiantes = listaReservas.json()["data"]["Estudiantes"]
            rutBuscar = elemento['rutMaker']
            idBuscado = None
            nombre = ""
            for i in estudiantes.get("rut"):
                if estudiantes.get("rut")[i] == rutBuscar:
                    idBuscado = i

            if idBuscado == None:
                nombre = " - "
            else:
                for i in estudiantes.get("nombre"):
                    if i == idBuscado:
                        nombre = estudiantes.get("nombre")[i]
        
            habilitacion['nombre'] = nombre
            listaHabilitados[elemento['id']] = habilitacion
        
        return JsonResponse(listaHabilitados, safe = False)

@csrf_exempt
def Si(request):
    if request.method == 'GET':
        tipo=request.GET.get('tipo_maquina')
        si = Habilitacion.objects.filter(habilitado_o_no='y').filter(tipo_maquina=tipo)
        si_S = HabilitacionesSerializer(si,many = True, context={'request': request})
        listaHabilitados = {}
        for elemento in si_S.data:
            habilitacion = {}
            habilitacion['rutMaker'] = elemento['rutMaker']
            habilitacion['tipo_maquina'] = elemento['tipo_maquina']
            habilitacion['habilitado_o_no'] = elemento['habilitado_o_no']
            habilitacion['recursos'] = elemento['recursos']

            listaReservas = requests.get("http://ec2-18-188-125-103.us-east-2.compute.amazonaws.com:5000/maker")

            estudiantes = listaReservas.json()["data"]["Estudiantes"]
            rutBuscar = elemento['rutMaker']
            idBuscado = None
            nombre = ""
            for i in estudiantes.get("rut"):
                if estudiantes.get("rut")[i] == rutBuscar:
                    idBuscado = i

            if idBuscado == None:
                nombre = " - "
            else:
                for i in estudiantes.get("nombre"):
                    if i == idBuscado:
                        nombre = estudiantes.get("nombre")[i]
        
            habilitacion['nombre'] = nombre
            listaHabilitados[elemento['id']] = habilitacion
        
        return JsonResponse(listaHabilitados, safe = False)

@csrf_exempt
def No(request): 
    if request.method == 'GET':
        tipo=request.GET.get('tipo_maquina')
        no = Habilitacion.objects.filter(habilitado_o_no='n').filter(tipo_maquina=tipo)
        no_S = HabilitacionesSerializer(no,many = True, context={'request': request})
        listaHabilitados = {}
        for elemento in no_S.data:
            habilitacion = {}
            habilitacion['rutMaker'] = elemento['rutMaker']
            habilitacion['tipo_maquina'] = elemento['tipo_maquina']
            habilitacion['habilitado_o_no'] = elemento['habilitado_o_no']
            habilitacion['recursos'] = elemento['recursos']

            listaReservas = requests.get("http://ec2-18-188-125-103.us-east-2.compute.amazonaws.com:5000/maker")

            estudiantes = listaReservas.json()["data"]["Estudiantes"]
            rutBuscar = elemento['rutMaker']
            idBuscado = None
            nombre = ""
            for i in estudiantes.get("rut"):
                if estudiantes.get("rut")[i] == rutBuscar:
                    idBuscado = i

            if idBuscado == None:
                nombre = " - "
            else:
                for i in estudiantes.get("nombre"):
                    if i == idBuscado:
                        nombre = estudiantes.get("nombre")[i]
        
            habilitacion['nombre'] = nombre
            listaHabilitados[elemento['id']] = habilitacion
        
        return JsonResponse(listaHabilitados, safe = False)

@csrf_exempt
def Add(req):
    if req.method == 'POST':
        nData = {
            'id_maker':req.GET.get('id_maker'),
            'id_ayudante':req.GET.get('id_ayudante'),
            'tipo_maquina':req.GET.get('tipo_maquina'),
            'habilitado_o_no':req.GET.get('habilitado_o_no'),
            'recursos':req.GET.get('recursos'),
            
        }

        serializerData = HabilitacionesSerializer(data = nData)
        if serializerData.is_valid():
            serializerData.save()
            return JsonResponse(serializerData.data, status=201)
        return JsonResponse(serializerData.errors, status = 400)

@csrf_exempt
def Update(req):
    if req.method == 'PUT':
            pk=req.GET.get('id')
            habilitacion = Habilitacion.objects.filter(id=pk)
            serializerData = HabilitacionesSerializer(instance=habilitacion, data = req.data)
            if serializerData.is_valid():
                serializerData.save()
                return JsonResponse(serializerData.data)
            return JsonResponse(serializerData.errors, status = 400) 

