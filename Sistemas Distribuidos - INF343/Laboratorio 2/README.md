# T2-Distribuidos
## Squid-Game

### INTEGRANTES:
- **Nazareth Diaz** - **201873560-4**
- **Jael Toledo** - **201873543-4**
- **Clemente Donoso** - **201873546-9**

Las máquinas virtuales están asociadas de la siguiente manera

**Para facilitar la corrección: No se implementaron los procesos de DataNode y NameNode**

| Máquina | Procesos |
|-------|-------- |
| dist69| Lider, DataNode |
| dist70| Pozo, DataNode, Jugadores|
| dist71| NameNode, Jugadores|
| dist72| DataNode, DataNode, Jugadores|

Es de suma importancia ejecutar en el siguiente orden las máquinas

| Lugar | Máquina |
|-------|-------- |
| 1| dist69|
| 2| dist70|
| 3| dist71|
| 4| dist72|

En cada máquina aparecerán las instrucciones correspondientes sobre como continuar.
### INSTRUCCIONES:
- Ejecutar el comando ``` $ sudo service rabbitmq-server start```
- Se debe ejecutar en la máquina dist69 el comando: ``` go run server.go ```
- Se debe ejecutar en la máquina dist70 el comando: ``` go run jugador.go ``` y así correr el jugador 1
- Se debe ejecutar en la máquina dist71 el comando: ``` go run jugador.go ``` y así correr el jugador 2
- Se debe ejecutar en la máquina dist72 el comando: ``` go run jugador.go ``` y así correr el jugador 3
De esta manera se estarán utilizando las 4 máquinas virtuales

Si se desean menos o más jugadores, se debe actualizar el MAKEFILE, el cual está pensado para 16 jugadores humanos.

### IMPORTANTE:

- Se asumirá que los jugadores son inteligentes, esto quiere decir que no eligiran valores extraños o valores fuera de los límites especificados en la tarea.
- El lider deberá contestar uno por uno a cada jugagador, para que así ninguno se quede atrás en el juego y tenga sentido la competencia, por favor, realizar este paso es de suma importancia para la realización de la tarea.
- Por falta de tiempo, no se implementaron los bots automatizados, por lo que si se requiere probar recomiendo utilizar varias instancias del jugador o probar con 1 o 2 jugadores.


