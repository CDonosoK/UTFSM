#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/*************************************************************************************************
*void init                                                                                       *
**************************************************************************************************
*Inicializa la lista enlazada con su cabeza, actual y cola apuntando a NULL.                     *
**************************************************************************************************
*Input: sin input.                                                                               *
**************************************************************************************************
*Returns: tLista* lista, retorna un puntero  a un contenedor de una enlazada.                    *
**************************************************************************************************/
tLista* init_lista(){
    tLista* lista = (tLista*)malloc(sizeof(tLista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->actual = NULL;
    lista->length = 0;
    return lista;
}
/*************************************************************************************************
*void insert                                                                                     *
**************************************************************************************************
*Inerta nodos en una posicion determinada de la lista,no admite mas de un parametro de posicion  *
**************************************************************************************************
*Input: Se le entrega un parametro de lista, un parametro de posicion de donde se insertara y    *           
*un parametro del dato que se insertara en la lista.                                             *
**************************************************************************************************
*Returns: No tiene retorno.                                                                      *
**************************************************************************************************/
void insert(tLista *lista, int pos , dato dat ){
    if ( (pos>lista->length)||(pos<lista->length) ){
        printf ("no se pudo insertar con exito\n");
        return;
    }
    if (0>pos){
        printf ("no se pudo insertar con exito\n");
        return;
    } 
    nodo *aux = (nodo*)malloc(sizeof(nodo));
    aux->info = dat;
    if (dat.tipo=='i'){
        int *a_i = malloc(sizeof(int));
        a_i = dat.contenido; 
        aux->info.contenido = a_i;
    }
    else if (dat.tipo=='f'){
        float *a_f = malloc(sizeof(float));
        a_f = dat.contenido;
        aux->info.contenido = a_f;
    }
    else{
        tLista *a_l = init_lista();
        a_l = dat.contenido;
        aux->info.contenido = a_l;//probar si es necesario crear un tlista en el make
        //lista->length--;
    }

    if ( lista->length==0 ){
        nodo *fantasma = (nodo*)malloc(sizeof(nodo));
        lista->tail = aux;
        lista->head = fantasma;
        fantasma->next = aux;
    }
    else if ( pos==lista->length ){
        lista->tail->next = aux;
        lista->tail = lista->tail->next;
    }
    else if ( pos==0 ){
        lista->actual = lista->head->next;
        lista->head->next = aux;
        aux->next = lista->actual;
    }
    else{//revisar este else
        int i;
        nodo *ant;
        lista->actual = lista->head->next;
        ant = lista->head;
        for ( i=0 ; i<=pos ; i++ ){
            lista->actual = lista->actual->next;
            ant = ant->next;
        }
        aux->next = lista->actual;
        ant->next = aux;
    }
    lista->length++;
    return;
}
/*************************************************************************************************
*void append                                                                                     *
******************************c********************************************************************
*Inserta nodos al final de la lista que se le ingrese                                            *
**************************************************************************************************
*Input:Se le entrega un parametro de lista, un parametro de posicion de donde se insertara.      *
**************************************************************************************************
*Returns: Sin retorno.                                                                           *
**************************************************************************************************/
void append(tLista *lista, dato dat){
    nodo *aux = (nodo*)malloc(sizeof(nodo));
    aux->info = dat;
    if (dat.tipo=='i'){
        int *a_i = malloc(sizeof(int));
        a_i = dat.contenido; 
        aux->info.contenido = a_i;
    }
    else if (dat.tipo=='f'){
        float *a_f = malloc(sizeof(float));
        a_f = dat.contenido;
        aux->info.contenido = a_f;
    }
    else{
        tLista *a_l = init_lista();
        a_l = dat.contenido;
        aux->info.contenido = a_l;//probar si es necesario crear un tlista en el make
        //lista->length--;
    }

    if ( lista->length==0 ){
        nodo *fantasma = (nodo*)malloc(sizeof(nodo));
        lista->tail = aux;
        lista->head = fantasma;
        fantasma->next = aux;
    }
    else {
        lista->tail->next = aux;
        lista->tail = lista->tail->next;
    }
    lista->length++;
    return;
}
/*void append(tLista *lista, dato dat, int prof){
    nodo *aux = (nodo*)malloc(sizeof(nodo));
    aux->info = dat;
    if (dat.tipo=='i'){
        int *a_i = malloc(sizeof(int));
        a_i = dat.contenido; 
        aux->info.contenido = a_i;
    }
    else if (dat.tipo=='f'){
        float *a_f = malloc(sizeof(float));
        a_f = dat.contenido;
        aux->info.contenido = a_f;
    }
    else{
        char *a_c = malloc(sizeof(char)*2);
        a_c = dat.contenido;
        aux->info.contenido = a_c;
        if (prof==1){
            printf("")
            if (*(char*)dat.contenido=='['){
                lista->length++;
            }
        }
        }

    if ( lista->length==0 ){
        nodo *fantasma = (nodo*)malloc(sizeof(nodo));
        lista->tail = aux;
        lista->head = fantasma;
        fantasma->next = aux;
    }
    else {
        lista->tail->next = aux;
        lista->tail = lista->tail->next;
    }
    if (prof==0){
        lista->length++;
    }
}*/
/*************************************************************************************************
*void clear                                                                                      *
**************************************************************************************************
*libera la memoria de todos los nodos de una lista enlazada                                      *
**************************************************************************************************
*Input:Se le entrega un parametro de lista la cual seran borrados los nodos                      *
**************************************************************************************************
*Returns: Sin retorno                                                                            *
**************************************************************************************************/
void clear(tLista *lista){
    nodo *loop_aux_next;
    lista->actual = lista->head;
        while (lista->head != NULL){
        loop_aux_next = lista->head;
        lista->head =  lista->head->next;
        free(loop_aux_next);
        }
    lista->length = 0;
    return;
}
/*************************************************************************************************
*void destroy                                                                                    *
**************************************************************************************************
*libera la memoria del struct tlista                                                             *
**************************************************************************************************
*Input:Un parametro lista la cual sera liberada,se recomienda liberar los nodos antes de invocar *
*esta funcion                                                                                    *
**************************************************************************************************
*Returns: Sin retorno.                                                                           *
**************************************************************************************************/
void destroy(tLista *lista){
    free((void*)lista);
    return;
}
/*************************************************************************************************
*void remove_algo                                                                                *
**************************************************************************************************
*Elimina un nodo en la posicion que se le ingrese.                                               *
**************************************************************************************************
*Input:Se le entrega un parametro de lista, un parametro de posicion de donde se insertara.      *
**************************************************************************************************
*Returns: Sin retorno.                                                                           *
**************************************************************************************************/
void remove_algo(tLista *lista, int pos){
    nodo *ant;
    lista->actual = lista->head->next;
    ant = lista->head;
    int i;
    for ( i=0 ; i<=pos ; i++ ){
        lista->actual = lista->actual->next;
        ant = ant->next;
    }
    ant->next = lista->actual->next;
    free(lista->actual);
    lista->length--;
    return;
}
/*************************************************************************************************
*int length                                                                                      *
**************************************************************************************************
*Retorna el largo en nodos de una funcion                                                        *
**************************************************************************************************
*Input:Se le entrega un parametro de lista.                                                      *
**************************************************************************************************
*Returns: tLista* lista, retorna un puntero  a un contenedor de una enlazada.                    *
**************************************************************************************************/
int length(tLista *lista){
    return lista->length;
}
/*************************************************************************************************
*dato* at                                                                                        *
**************************************************************************************************
*Retorna nodos del tipo dato en la posicion indicada                                             *
**************************************************************************************************
*Input:Se le entrega un parametro de lista, un parametro de posicion de donde se insertara.      *
**************************************************************************************************
*Returns: un "dato" de la posicion que se indico                                                 *
**************************************************************************************************/
dato* at(tLista *lista, int pos){
    lista->actual = lista->head->next;
    int i;
    for ( i=0 ; i<=pos ; i++ ){
        lista->actual = lista->actual->next;
    }
    return &lista->actual->info;
}
