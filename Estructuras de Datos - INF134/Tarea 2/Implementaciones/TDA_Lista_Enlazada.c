#include <stdio.h>
#include <stdlib.h>

/*Funciones de una Lista:
-initialize() - iniciliza la lista
-clear() - borra los contendios
-moveToStart() - mueve el cursor al incio
-moveToEnd() - mueve el cursor al final
-int next() - mueve cursor +1 posicion
-int prev() - mueve el cursor -1 posicion
-append(item) - agrega item al final de la lista
-insert(item) - agrega en posicion actual
-remove(pos) - borra elemento en posicion pos
-int length() - retorna el largo de la lista
-int currpos() - retorno la posicion actual del cursor
-void moveToPos(pos) - mueve el cursos a la posicion pos
-tElemLista getValue() - retorna el valor actual al que apunta el cursor
-delete() - borra la estructura contenedora de la lista
*/

typedef int tElemLista;

typedef struct nodo{
  tElemLista elem;
  struct nodo *next; //puntero autoreferrencial al siguiente nodo
}tNode;

typedef struct tLista{
  tNode *head;
  tNode *tail;
  tNode *curr;
  int listSize;
  int currpos;
}tLista;


void destroy();
tLista* initialize();
void clear(tLista *lista);

/*******************************************************************************
*iniciliza la lista enlazada.                                                  *
*******************************************************************************/
tLista* initialize(){
  tLista* lista = (tLista*)malloc(sizeof(tLista));
  //head,tail y curr exigen malloc por guardar un puntero y un elemento.
  lista->head = NULL;
  lista->tail = NULL;
  lista->curr = NULL;
  lista->listSize = 0;
  lista->currpos = 0;
  return lista;
}

/*******************************************************************************
*Borra cada nodo existente.                                                    *
*******************************************************************************/
void clear(tLista *lista){
  //loop_aux_next no exige malloc por ser un puntero referencial.
  tNode *loop_aux_next;
  lista->curr = lista->head;
    while (lista->head != NULL){
    loop_aux_next = lista->head;
    lista->head =  lista->head->next;
    free(loop_aux_next);
    }
  lista->listSize = 0;
  lista->currpos = -1;
}

/*******************************************************************************
*Mueve el cursor al incio (head) de la lista.                                  *
*******************************************************************************/
void moveToStart(tLista *lista){
  lista->currpos = 0;
  lista->curr = lista->head;
}


/*******************************************************************************
*Mueve el cursor al final.                                                     *
*******************************************************************************/
void moveToEnd(tLista *lista){
  lista->curr = lista->tail;
  lista->currpos = lista->listSize;
}


/*******************************************************************************
*Avanza el cursor (+1).                                                        *
*******************************************************************************/

void next(tLista *lista){
  if (lista->curr != lista->tail && lista->listSize > 0){
    lista->curr = lista->curr -> next;
  }
}

/*******************************************************************************
*Retrocede el cursor (-1)                                                      *
*******************************************************************************/
void prev(tLista *lista){
  tNode *temp;
  if (lista->curr == lista->head){
    return;
  }
  temp = lista->head;
  while (temp-> next != lista->curr){
  temp = temp->next;
  }
  lista->curr = temp;
  lista->currpos--;
}

/*******************************************************************************
*Retorna  el largo de la lista.                                                *
*******************************************************************************/

int length(tLista *lista){
  return lista->listSize;
}

/*******************************************************************************
*Retorna la posicion actual.                                                   *
*******************************************************************************/

int currpos(tLista *lista){
  return lista->currpos;
}

/*******************************************************************************
*Mueve el cursor a la posicion pos.                                            *
*******************************************************************************/
void moveToPos(tLista *lista,int pos){
  if (lista->currpos < 0 || lista->currpos > lista->listSize){
    return;
  }
  lista->curr = lista->head;
  lista->currpos = 0;
  for (int i = 0; i < pos; i++){
  //  lista.curr = lista.curr->next;
    lista->currpos ++;
  }
}

/*******************************************************************************
*Inserta elemento en tail.                                                     *
*******************************************************************************/
void append(tLista *lista,tElemLista item){
  //exige un malloc por guardar un elemento.
  tNode *aux = (tNode*)malloc(sizeof(tNode));
  aux->elem = item;
  aux->next = NULL;

  if (lista->head ==  NULL){
    lista->head =  aux;
    lista->tail = aux;
    lista->curr = aux;
  }
  else{
    lista->tail-> next = aux;
    lista->tail = aux;
  }
  lista->listSize++;
}

/*******************************************************************************
*Inserta item en posicion indicada.                                            *
*******************************************************************************/
void insert(tLista *lista,tElemLista item,int pos){
  if (pos == 0 && lista->listSize == 0){
    printf("La lista es vacia. Llamando al append.\n");
    append(lista,item);
    return;
  }
  if(pos ==  lista->listSize){
    printf("Se requiere insertar al final de la lista.\n");
    append(lista,item);
    return;
  }
  //dado que es un nuevo NODO entero que se le agregara a la lista,
  //le asignamos un malloc ( no es un puntero simple.)
  tNode *aux = (tNode*)malloc(sizeof(tNode));
  aux->elem = item;
  if(pos == 0 && lista->listSize != 0){

    printf("Se requiere insertar al inicio en lista no vacia.\n");
    aux->next = lista->head;
    lista->head = aux;
    lista->listSize ++;
  }
  else{
    printf("Se requiere insertar en posicion %d de la lista no vacia.\n",pos);
    if (pos > lista->listSize-1){
      return;
    }
    int k;
    //dado que loop es un puntero, no tenemos que hacer el malloc
    tNode *loop_aux;
    loop_aux = lista->head;
    for (k = 0; k < pos-1; k++){
      loop_aux = loop_aux->next;
    }
    aux->next = loop_aux->next;
    loop_aux->next = aux;
    lista->listSize ++;
    }
}


/*******************************************************************************
*Borra el elemento en posicion pos                                             *
*******************************************************************************/
void remov(tLista *lista,int pos){
  if(lista->listSize == 0 || pos > lista->listSize-1 || pos < 0){
    printf("O la lista es vacia, o el indice out of bounds.\n" );
    return;
  }
  tNode *aux;
  //eliminar al inicio. Tenemos que guardar el puntero al curr para
  //despues poder liberar la memoria.
  if (pos == 0 && lista->listSize != 0){
    printf("Se requiere borrar el primer elemento de lista no vacia.\n");
    aux = lista->head;
    lista->head = aux->next;
    lista->listSize --;
    free(aux);
    return;
  }
  tNode *loop_aux;
  loop_aux = lista -> head;
  int k;
  for(k=0;k<pos-1;k++){
    loop_aux = loop_aux->next; // recorre hasta pos-1,loop_aux es el elemento pos-1,apunta a pos;
  }
  //eliminar al final
  if (pos == lista->listSize-1){
    printf("Se requiere borrar al final\n");
    aux = loop_aux->next;
    loop_aux -> next = NULL;
    lista->tail = loop_aux;
    lista->listSize--;
    free(aux);
    return;
  }
  //eliminar dentro de la lista, no en un extremo
  else{
    printf("Se requiere borrar en la posicion %d.\n",pos);
    aux = loop_aux->next;
    loop_aux->next = loop_aux->next->next;
    free(aux);
  }
  lista->listSize--;
}

/*******************************************************************************
*Retorna el valor actual.                                                      *
*******************************************************************************/

tElemLista getValue(tLista *lista){
  return lista->curr->elem;
}

/*******************************************************************************
*Borra la lista.                                                               *
*******************************************************************************/

void destroy(tLista *lista){
  free((void*)lista);
}

/*******************************************************************************
*Imprime la lista.                                                             *
*******************************************************************************/

void printout(tLista *lista){
  if (lista->listSize == 0){
    printf("{}\n");
    return;
  }
  //notar que aux es un puntero, por ende no exige malloc.
  tNode *aux;
  aux = lista->head;
  printf("{");
  while (aux != NULL){
    printf("%d->",aux->elem);
    aux = aux->next;
  }
  printf("NULL}\n");
}


/*******************************************************************************
*                                   *                                          *
*******************************************************************************/
int main(void){

  tLista *lista = initialize();
  printout(lista);//lista vacia

  printf("Largo: %d\n",length(lista));
  printf("%d\n",currpos(lista) );


  insert(lista,10,0);
  insert(lista,1,1);
  insert(lista,9,0);
  insert(lista,44,1);
  insert(lista,4,2);
  insert(lista,18,5);
  printf("Largo: %d\n",length(lista)); //6
  printout(lista); //nueva lista {9 44 4 10 1 18}

  moveToPos(lista,3);
  printf("Nueva pos: %d\n",currpos(lista) ); //3

  moveToEnd(lista);
  printf("Nueva pos: %d\n",currpos(lista)); //5

  moveToStart(lista);
  printf("Nueva pos: %d\n",currpos(lista) ); //0

  printf("Current: %d\n",getValue(lista)); //9, dado que curr = 0.
  next(lista);
  printf("Current: %d\n",getValue(lista)); //44, dado que curr = 1.
  next(lista);
  printf("Current: %d\n",getValue(lista));
  next(lista);
  printf("Current: %d\n",getValue(lista));
  next(lista);
  printf("Current: %d\n",getValue(lista));
  next(lista);
  printf("Current: %d\n",getValue(lista)); //18
  next(lista); // ya no hace nada porque estamos en cola.
  printf("Current: %d\n",getValue(lista)); //18

  prev(lista);
  printf("Current: %d\n",getValue(lista));
  prev(lista);
  printf("Current: %d\n",getValue(lista));
  prev(lista);
  printf("Current: %d\n",getValue(lista));
  prev(lista);
  printf("Current: %d\n",getValue(lista));
  prev(lista);
  printf("Current: %d\n",getValue(lista));
  prev(lista); // ya no hace nada porque estamos en la cabeza
  printf("Current: %d\n",getValue(lista));

  remov(lista,0); //remueve elemento en pos
  printout(lista); //nueva lista { 44 4 10 1 18}
  printf("Largo:%d\n", length(lista)); //4

  clear(lista); //reinicia el array
  printout(lista);
  printf("Largo:%d\n",length(lista)); //0
  destroy(lista); //borra todo
}
