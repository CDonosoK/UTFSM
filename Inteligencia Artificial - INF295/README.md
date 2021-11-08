# Examination Timetabling Problem Solver

El presente proyecto consta de una investigación realizada para el curso de Inteligencia Artificial, dicha investigación tiene como objetivo presentar el estado del arte del problema Examination Timetabling Problem, como también se presenta una solución al problema utilizando un algoritmo Greedy para obtener una solución inicial, y luego un algoritmo HillClimbing para mejorar la calidad de dicha solución. El resultado
conlleva a que ningún estudiante tendrá que rendir 2 o más exámenes al mismo tiempo, utilizando la mínima cantidad posible de timeslot u horarios.
Si bien el problema también pide minimizar la penalización que tienen los estudiantes, se observó que la minimización de los horarios, conlleva a 
una minimización de la penalización.

## Archivos disponibles

En el repositorio se pueden encontrar una serie de carpetas, las cuales contienen el trabajo realizado durante el semestre, así como la investigación, código, instancias experimentales y más.

* El directorio consta del archivo etpSolver.cpp el cual contiene el código para resolver el problema.
* [paperIncial](./paperIncial): Carpeta que contiene el código latex y PDF generado, de la investigación inicial.
* [paperFinal](./paperFinal): Carpeta que contiene el código latex y PDF generado, de la investigación final.
* [Instancias](./Instancias): Carpeta que contiene las instancias de prueba para el ETP.
* [Respuestas](./Respuestas): Carpeta que contiene los archivos generados al momento de probar una instancia, estos son los archivos de los timeslot totales, la penalización promedio, y en qué bloque quedaron asignados cada examen.


## Instrucciones la Ejecución del ETPSolver

* Compilar el ETPSolver con `make`
* Ejecutar con `./ETPSolver`
* Al momento de ejecutar se le pedirá que ingrese el nombre de alguno de los archivos, los cuales deben estar en la carpeta instancias.
* Para eliminar los residuos de compilación, así como el programa, ejecutar `make clean`
* En caso de existir algún problema, se da acceso al ejecutable "etpSolver.exe".


