#include <stdio.h>
#include <stdlib.h>

/* COLAS- QUEUE - tipo FIFO
first in first out

operaciones en cola
- clear() - limpia la cola
- int enqueue() - inserta un elemento al final de la cola
-void dequeue() - elimina un elemento de la cabeza de la cola
-tElemCola frontValue() - retorna el elemento de cabeza
-int size() - retorna el size de la cola*/

typedef int tElemQueue;

tElemQueue *queue;
int queueSize;
int head;
int tail;
int maxSize;

void initialize();
void dequeue();
int enqueue();
tElemQueue frontValue();
int size();

#define MAXSIZE 5

/*******************************************************************************
*Inizializa la cola.                                                           *
*******************************************************************************/
void initialize(){
  queue = malloc(sizeof(tElemQueue)*MAXSIZE);
  maxSize = MAXSIZE;
  queueSize = 0;
  head = -1;
  tail = -1;
}
/*******************************************************************************
*Reinicializa una cola como vacia.                                             *
*******************************************************************************/
void clear(){
  free((void*)queue);
  initialize();
}

/*******************************************************************************
*Agrega un elemento a la cola.                                                 *
*******************************************************************************/
int enqueue(tElemQueue item){
  // cola llena
  if (queueSize == maxSize) {
    return -1; // no hay espacio.
  }
  //cola vacia
  else if (tail == -1){
    tail = head = 0;
    queue[tail] = item;
  }
  //tail esta al final del array pero este no esta lleno todavia
  //entonces hay espacio desde posicion 0 hasta head
  else if ( tail == maxSize - 1 && queueSize < maxSize){
    tail = 0;
    queue[tail] = item;
  }
  //hay espacio despues de tail, podemos insertar ahi.
  else{
    tail++;
    queue[tail] = item;
    }
  queueSize++;
  return 0; // insercion exitosa.
}

/*******************************************************************************
*Avanza la cabeza, sacando el primer elemento de la cola.                      *
*******************************************************************************/
void dequeue(){
  //cola vacia.
  if (head == -1){
    return;
  }
  else if (head == tail){
    head = tail = -1; //cola vacia
  }
  else if (head == maxSize-1){
    head = 0;
  }
  else{
    head++;
  }
  queueSize--;
}

/*******************************************************************************
*Retorna la cabeza de la cola.                                                 *
******************************************************************************/
tElemQueue frontValue(){
  if (head != -1){
  return queue[head];
  }
}
/*******************************************************************************
*Borra la cantidad de elementos de queue.                                      *
*******************************************************************************/

int size(){
  return queueSize;
}

/*******************************************************************************
*Imprimie la cola.                                                             *
*******************************************************************************/
void printout(){
  if (queueSize == 0){
    printf("[]\n");
    return;
  }
  printf("[");
  for (int i = 0;i<maxSize; i++){
    if(i == tail){
      printf("TAIL:%d ",queue[i]);
    }
    else if(i == head){
      printf("HEAD:%d ",queue[i] );
    }
    else{
      printf("%d ",queue[i] );
    }
  }
  printf("]");
}

/*******************************************************************************
*Borra la cola contenedora.                                                    *
*******************************************************************************/
void destroy(){
  free((void*)queue);
}

/*******************************************************************************
*                                   *                                          *
*******************************************************************************/

int main(void){
  initialize();
  printf("Size : %d\n",size());

  enqueue(3);
  enqueue(1);
  enqueue(10);
  enqueue(2);
  enqueue(9);
  printout();
  printf("\nSe aplicara un dequeue\n");
  dequeue();
  printf("Size: %d\n",size() );
  printf("7 a insertar\n" );
  enqueue(7);
  printf("Size: %d\n",size() );
  printout();

  dequeue();
  dequeue();

  enqueue(19);
  printf("\n");
  printf("Size: %d\n",size() );
  printout();
  printf("\n");
  destroy();
}
