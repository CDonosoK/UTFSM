#include <stdio.h>

/*************************************************************************************************
*Declaraciones de las funciones utilizadas.                                                      *
**************************************************************************************************/

tLista* init_lista(tLista *a); // se queda
void insert(tLista *lista, int pos , dato dat); // se queda
void clear(tLista *lista); // se queda
void append(tLista *lista, dato dat); // se queda
void destroy(tLista *lista); // se queda
void remove_algo(tLista *lista, int pos); // se queda
int length(tLista *lista);
dato* at(tLista *lista, int pos);
float sum(struct tLista* lista);
void print(struct tLista* lista);
float average(struct tLista* lista)
