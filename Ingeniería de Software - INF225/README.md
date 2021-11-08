# Proyecto-ISW
Proyecto que consiste en crear una API para FabLab USM durante el curso ISW (Ingeniería de Software - 2021-1).
Específicamente la API maneja el contexto de recursos, el cual está compuesto por las máquinas, los recursos que se necesitan para habilitar y las habilitaciones de las personas máquinas.
Internamente, se realiza una verificación con 2 API (contextos gestión y personas), por lo que si se quiere utilizar deberá modificar el archivo views.py y eliminar dicha sección.


### Como se ejecuta:
En la terminal debe ingresar el siguiente comando: "py manage.py runserver"

### Cambios a los modelos:
Cualquier cambio que se realice a los modelos, se debe importar ejecutando los siguientes comandos:
<br>
[1] py manage.py makemigrations <br>
[2] py manage.py migrate

### Modelo de Dominio

![alt text](https://github.com/CDonosoK/Proyecto-ISW/blob/main/Modelos/Modelo%20de%20Dominio.PNG)


### Modelo de Contextos
![alt text](https://github.com/CDonosoK/Proyecto-ISW/blob/main/Modelos/Modelo%20de%20Contextos.PNG)

