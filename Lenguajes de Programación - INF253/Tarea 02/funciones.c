#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "lista.c"
//#include "lista.h"


typedef struct dato {
    void *contenido ;
    char tipo ;
} dato;
typedef struct nodo {
    dato info ;
    struct nodo * next ;
} nodo;
typedef struct tLista {
    nodo *actual ;
    nodo *head ;
    nodo *tail ;//ultimo en ser insertado
    int length ;
} tLista;

/*
tLista* map                                                                                      
--------------------------------------------------------------------------------------------------
 La operaci�n se le aplica a todos los elementos de la lista. Se consideran las operaciones
 de la forma '+', el cual ser� sumar el dato a todos los elementos de la lista, '-', el cual
 ser� restar el dato a todos los elementos de la lista, 'x' multiplicar el dato a todos los 
 elementos de la lista y '/' dividir por el dato a todos los elementos de la lista.    
--------------------------------------------------------------------------------------------------
Inputs: 
(struct tLista* lista) Puntero a una lista  
(char funcion ) operacion que podr� ser suma ('+'), resta ('-'), multiplicaci�n ('x') y
divisi�n ('/').
(int numero) numero por el cual la operacion ser� realizada                                          
--------------------------------------------------------------------------------------------------
Returns: 
(tLista * listaFinal) Puntero a la lista modificada                                       
*/
tLista* map(tLista* lista, char funcion, int numero)
{
	tLista* listaFinal = (tLista* )malloc(sizeof(tLista));
	int posicion = 0;
	int largo = lista->length;
	if (funcion == '+'){
		nodo *nodoActual = (nodo*)malloc(sizeof(nodo));
		nodoActual = lista->head;
		nodoActual->info.contenido += numero;
		listaFinal->head = nodoActual;
		listaFinal->actual = nodoActual;
		while(nodoActual != NULL){
			nodoActual = nodoActual->next;
			nodoActual->info.contenido += numero;
			listaFinal->actual = listaFinal->actual->next;
		}
	}
	if (funcion == '-'){
		nodo *nodoActual = (nodo*)malloc(sizeof(nodo));
		nodoActual = lista->head;
		nodoActual->info.contenido -= numero;
		listaFinal->head = nodoActual;
		listaFinal->actual = nodoActual;
		while(nodoActual != NULL){
			nodoActual = nodoActual->next;
			nodoActual->info.contenido += numero;
			listaFinal->actual = listaFinal->actual->next;
		}
	}
	return listaFinal;
}

/*
float sum                                                                                       
--------------------------------------------------------------------------------------------------
Suma todos los componentes de la lista, si esta est� vac�a la suma ser� 0                       
--------------------------------------------------------------------------------------------------
Inputs: 
(tLista* lista) Puntero a una lista                                                       
--------------------------------------------------------------------------------------------------
Returns: 
(float suma) Suma de todos los n�meros de la lista                                        
*/
float sum(struct tLista* lista)
{
	nodo *nodoActual = (nodo*)malloc(sizeof(nodo));
	nodoActual = lista->head;
	float suma = 0.0;
	if (nodoActual == NULL){
		return suma;
	}
	else{
		float s = *((float *)(nodoActual->info).contenido);
		suma += s;
		while (nodoActual != NULL){
			nodoActual = nodoActual->next;
			float s = *((float *)(nodoActual->info).contenido);
			suma += s;
		}
	}
	return suma;
}

/*
void print                                                                                     
--------------------------------------------------------------------------------------------------
Imprime de forma ordenada y clara la lista enlazada y tambi�n, las sub-listas enlazadas tambi�n 
--------------------------------------------------------------------------------------------------
Inputs: 
(tLista* lista) Puntero a una lista                                                       
--------------------------------------------------------------------------------------------------
Returns: 
                                                                        
*/
void print(struct tLista* lista)
{
	nodo *nodoActual = (nodo*)malloc(sizeof(nodo));
	nodoActual = lista->head;
	if (nodoActual->info.tipo == 'f'){
		printf("%f -->",nodoActual->info.contenido );
	}
	else{
		printf("%i -->",nodoActual->info.contenido );
	}
	
	if (nodoActual == NULL){
		printf("la lista est� vac�a");
	}
	else{
		while (nodoActual != NULL){
			nodoActual = nodoActual->next;
			if (nodoActual->info.tipo == 'f'){
				float s = *((float *)(nodoActual->info).contenido);
				printf("%f -->",s );
			}
			else{
				int s = *((int *)(nodoActual->info).contenido);
				printf("%i -->",s );
			}
		}
	}
}

/*
float average                                                                                   
--------------------------------------------------------------------------------------------------
Calcula el promedio de los datos de la lista. Esta funci�n utiliza la funci�n sum               
--------------------------------------------------------------------------------------------------
Inputs: 
(tLista* lista) Puntero a una lista                                                       
--------------------------------------------------------------------------------------------------
Returns: 
(float promedio) Promedio de todos los n�meros de la lista                                
*/

float average(struct tLista* lista)
{
	nodo *nodoActual = (nodo*)malloc(sizeof(nodo));
	nodoActual = lista->head;
	float suma, promedio;
	int cantidad;
	cantidad = lista->length;
	suma = sum(lista);
	promedio = (suma/cantidad);
	return promedio;
}

void main(){
	
}
