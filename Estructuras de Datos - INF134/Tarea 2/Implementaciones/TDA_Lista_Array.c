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
-remove() - borra elemento en posicion actual
-int length() - retorna el largo de la lista
-int currpos() - retorno la posicion actual del cursor
-void moveToPos(pos) - mueve el cursos a la posicion pos`
-tElemLista getValue() - retorna el valor actual al que apunta el cursor
-delete() - borra la estructura contenedora de la lista
*/

typedef int tElemLista;

tElemLista *tLista;
int listSize;
int curr;
int maxSize;


#define MAXSIZE 100000

/*******************************************************************************
*Pasa memoria suficiente y inicia las variables asociadas a la lista.          *
*******************************************************************************/

void initialize(){
    tLista = (tElemLista*)malloc(MAXSIZE*sizeof(tElemLista)); //malloc de memoria
    listSize = 0; //lista vacia
    curr = 0; //actual posicion,por ahora la lista es vacia, pero se asume que no lo sera
    maxSize = MAXSIZE; //cambia el maximo rango de array.
}

/*******************************************************************************
*Limpia la memoria alocada y reinicia la lista.                                *
*******************************************************************************/

void clear(){
  free((void*)tLista);
  initialize();
}

/*******************************************************************************
*Reinicia la posicion, cambiando el indice actual a 0.                         *
*******************************************************************************/

void moveToStart(){
  curr = 0;
}

/*******************************************************************************
*Reinicia la posicion, cambiando el indice actual al de ultimo elemento.       *
*******************************************************************************/

void movetoEnd(){
  curr = listSize;
}

/*******************************************************************************
*Aumenta el indice posicion,avanzando. En caso de estar en cola, no hace nada. *
*******************************************************************************/

void next(){
  if (curr < listSize){
    curr++;
  }
}

/*******************************************************************************
*Disminuye el indice de posicion, retrocediendo. En caso de estar en cabeza,no *
*hace nada.                                                                    *
*******************************************************************************/

void prev(){
  if (curr != 0){
    curr--;
  }
}

/*******************************************************************************
*Agrega el elemento en la ultima posicion de la lista.                         *
*******************************************************************************/

int append(tElemLista item){
  if (listSize >=  maxSize){
    return 0; //no se puede insertar nada
  }
  tLista[listSize++] = item;
  return 1; //insercion exitosa
}

/*******************************************************************************
*Inserta un elemento en posicion curr                                          *
*******************************************************************************/

int insert(tElemLista item){
  int i;
  if (listSize >= maxSize){
    return -1; //lista llena.
  }
  for (i = listSize; i > curr; i--){
    tLista[i] = tLista[i-1];
  }
    tLista[i] = item;
    listSize ++;
  return i; //retorna posicion donde se inserta el elemento item.
}

/*******************************************************************************
*Reasigna la posicion actual.                                                  *
*******************************************************************************/

void moveToPos(int pos){
  curr = pos;
}

/*******************************************************************************
*Obtiene el valor actual.                                                      *
*******************************************************************************/

tElemLista getValue(){
  if (curr < 0 || curr >= listSize){
    return 0;
  }
  return tLista[curr];
}

/*******************************************************************************
*Obtiene el largo de la lista.                                                 *
*******************************************************************************/

int length(){
  return listSize;
}

/*******************************************************************************
*Retorna la posicion actual.                                                   *
*******************************************************************************/

int currPos(){
  return curr;
}

/*******************************************************************************
*Borra la lista.                                                               *
*******************************************************************************/

void delete(){
  clear();
  free((void*)tLista);

}

/*******************************************************************************
*Imprime la lista.                                                             *
*******************************************************************************/

void printout(){
  int i;
  printf("{");
  for (i = 0; i< listSize; i++){
    printf("%d ",tLista[i]);
  }
  printf("}\n");
}

/*******************************************************************************
*Saca el valor de la lista y retorna este.                                     *
*******************************************************************************/

tElemLista remov(){
  int i;
  tElemLista  item;
  if (curr < 0 || curr >= listSize){
    return -1;
  }
  item = tLista[curr];
  for (i = curr; i < listSize-1; i++){
    tLista[i] = tLista[i+1]; //desplaza todo hacia curr acortando asi el arreglo
  }
  listSize --;
  return item;
}

/*******************************************************************************
*                                   *                                          *
*******************************************************************************/
int main(void){
  initialize();
  printout();//lista vacia

  printf("Largo: %d\n",length()); //0
  printf("%d\n",curr ); //0

  insert(3);
  insert(1);
  insert(9);
  insert(44);
  insert(4);
  printf("Largo: %d\n",length()); //5
  printout(); //nueva lista {4 44 9 1 3}

  moveToPos(3);
  printf("Nueva pos: %d\n",curr ); //3

  movetoEnd();
  printf("Nueva pos: %d\n",curr); //5

  moveToStart();
  printf("Nueva pos: %d\n",curr ); //0

  remov(); //remueve elemento actual,curr = 0;
  printout(); //nueva lista {44 9 1 3}
  printf("Largo:%d\n", length()); //4

  clear(); //reinicia el array
  printout(); //{}
  printf("Largo:%d\n",length()); //0
  delete(); //borra todo
}
