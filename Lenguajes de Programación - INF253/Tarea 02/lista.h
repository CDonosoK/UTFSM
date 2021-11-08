#ifndef lista_h
#define lista_h

#include <stdio.h>

/*************************************************************************************************
*Declaracion de la estructura de la lista enlazada.                                              *
**************************************************************************************************/

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

/*************************************************************************************************
*Declaraciones de las funciones utilizadas.                                                        *
**************************************************************************************************/

tLista* init_lista(); // se queda
void insert(tLista *lista, int pos , dato dat); // se queda
void clear(tLista *lista); // se queda
void append(tLista *lista, dato dat); // se queda
void destroy(tLista *lista); // se queda
void remove_algo(tLista *lista, int pos); // se queda
int length(tLista *lista);
dato* at(tLista *lista, int pos);
void imprimir(tLista *lista);
#endif lista_h

