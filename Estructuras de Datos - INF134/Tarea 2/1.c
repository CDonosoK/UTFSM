#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************************************************
*Declaracion de la estructura de la lista enlazada.                                              *
*Cada nodo almacena su byte de inicio (limite inferior), byte final (limite superior) y un       *
*puntero al siguiente nodo de la lista.La estructura de la lista contiene informacion sobre el   *
*nodo de cabeza y de cola,y, ademas, el size de la lista.                                        *
**************************************************************************************************/

typedef int tElemLista;

typedef struct nodo{
  tElemLista firstByte;
  tElemLista lastByte;
  struct nodo *next;
}tNode;

typedef struct tLista{
  tNode *head;
  tNode *curr;
  tNode *tail;
  int currpos;
  int listSize;
}tLista;

/*************************************************************************************************
*Declaracion de una variable grande, utilizada como el analogo de inf en funcion de distancia.   *                                   *
**************************************************************************************************/

#define INFINITY 1000000

/*************************************************************************************************
*Declaraciones de las funciones utilizadas.                                                        *
**************************************************************************************************/

tLista* initialize();
void FirstFit(tLista *l1,tLista *l2,int m,FILE *wp);
void insert(tLista *lista,int fbyte,int lbyte ,int pos);
void clear(tLista *lista);
void append(tLista *lista,int fbyte,int lbyte);
void destroy(tLista *lista);
void printout(tLista *lista);
void splitAndAdjust(tLista *l1,tNode *Node,int freeByte);
double dist(int x1,int x2,int y1,int y2);
int optiPos(tLista *lista,int firstByte,int lastByte);
void removeFromAvailable(tLista *lista, int pos);
void merge(tLista *lista);
void newFree(tLista *l1,tLista *l2,int fbyte,FILE *wp);

/*************************************************************************************************
*void FirstFit                                                                                   *
**************************************************************************************************
*Funcion actua como el analago de malloc. Se separa en tres casos.                               *
*Caso 1: First fit no ideal.Se "separa" el bloque que cumple las condiciones, actualizando sus   *
*primero y ultimo byte. A la lista 2 se agrega un nodo con primerByte igual al primer byte de    *
*nodo de la lista 1 antes de actualizar y el ultimo byte igual a primer byte + size m - 1.       *
*Caso 2: First fit ideal. Se borra el bloque asignado de la lista 1, de manera quese mantiene la *
*conexion con el nodo subsiguiente y se agrega el nodo borrado a la lista 2.                     *
*Caso 3: Los bloques que existen no cumplen con la condicion exigida. Se asume que la lista 1    *
*utilizada ya ha pasado por el proceso de merge de bloques contiguos.                            *
*Se avisa que el bloque de X bytes no puede ser asignado y se termina la ejecucion.              *
**************************************************************************************************
*Input: tLista *l1 - puntero a lista con memoria libre.                                          *
*       tLista *l2 -puntero a la lista con memoria ocupada..                                     *
*       int m - size de bloque para el malloc                                                    *
*       FILE *wp - puntero al archivo de escritura.                                              *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void FirstFit(tLista *l1,tLista *l2,int m,FILE *wp){
  if(l1->head == NULL){
    fprintf(wp,"Bloque de %d bytes NO puede ser asignado\n",m );
    return;
  }
  int posInL1 = 0;
  tNode *aux;
  int blockSize,b;
  aux = l1->head;
  while(aux != NULL ){
    blockSize = aux->lastByte - aux->firstByte + 1;
    b = aux->firstByte;
    if(m < blockSize){
      aux->firstByte = b + m;
      fprintf(wp,"Bloque de %d asignado a partir del byte %d\n",m,b);
      insert(l2,b,m+b-1,0);
      return;
    }
    if(m == blockSize){
      removeFromAvailable(l1,posInL1);
      insert(l2,b,m+b-1,0);
      fprintf(wp,"Bloque de %d asignado a partir del byte %d\n",m,b);
      return;
    }
    posInL1++;
    aux = aux->next;
  }
  fprintf(wp,"Bloque de %d bytes NO puede ser asignado\n",m );
}

/*************************************************************************************************
*void removeFromAvailable                                                                        *
**************************************************************************************************
*Elimina un nodo de la lista, manteniedno las propiedades de la lista enlazada.Para eliminar en  *
*la posicion que no corresponde al extremo de la lista, recoremos esta hasta pos-1, obteniendo un*
*puntero loop_aux que apunta con next al nodo a liberar, de modo que podemos liberar su next y   *
*actualizarlo para mantener la lista enlazada sin perdida de conexiones.                         *
**************************************************************************************************
*Input:  tLista *lista - puntero a la lista a actualizar.                                        *
         int pos - posicion de nodo a eliminar.                                                  *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void removeFromAvailable(tLista *lista, int pos){
  if(lista->listSize == 0 || pos > lista->listSize-1 || pos < 0){
    return;
  }
  tNode *aux;
  //Caso 1. Eliminar al inicio de la lista.
  if (pos == 0 && lista->listSize != 0){
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
    loop_aux = loop_aux->next;
  }
  //Caso 2: eliminar al final de la lista.
  if (pos == lista->listSize-1){
    aux = loop_aux->next;
    loop_aux -> next = NULL;
    lista->tail = loop_aux;
    lista->listSize--;
    free(aux);
    return;
  }
  //Caso 3: eliminar en posicion pos.
  else{
    aux = loop_aux->next;
    loop_aux->next = loop_aux->next->next;
    free(aux);
  }
  lista->listSize--;
}

/*************************************************************************************************
*void newFree                                                                                    *
**************************************************************************************************
*Funcion analoga a free.Se separa en multiples casos, los cuales se organizan, usando 3 flags.   *
*Flag 1 corresponde a la situacion cuando se debe liberar un nodo cuyo firstByte coincide con    *
*el byte para hacer el free. Se libera el nodo encontrado, insertandolo en la lista con memoria  *
*libre.                                                                                          *
*Flag 2 corresponde al caso cuando el byte para hacer el free esta dentro de un nodo y no en sus *
*extremos.En este caso,se "separa" el nodo encontrado, usando la funcion splitAndAdjust.         *
*Flag 3 corresponde al caso cuando el byte a partir del cual se debe liberar corresponde al      *
*ultimo byte de algun nodo. En este caso, se considera el free como "free sin efecto", dado que  *
*no existe ningun bloque, que empieza con este byte.                                             *
**************************************************************************************************
*Input: tLista *l1 - puntero a lista con memoria libre.                                          *
*       tLista *l2 -puntero a la lista con memoria ocupada.                                      *
*       int m - primer byte  de bloque para free.                                                *
*       FILE *wp - puntero al archivo de escritura.                                              *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void newFree(tLista *l1,tLista *l2,int fbyte,FILE *wp){
  tNode *prevNode;
  tNode *loop_aux;
  tNode *aux;
  loop_aux = l2->head;
  prevNode = l2->head;
  int auxCount = 0;
  if (loop_aux == NULL){
    return;
  }
  int flag_1,flag_2,flag_3,blockSize;
  while(loop_aux != NULL){
    flag_1 = (loop_aux->firstByte == fbyte);
    flag_2 = (fbyte > loop_aux->firstByte && fbyte < loop_aux->lastByte);
    flag_3 = (fbyte == loop_aux->lastByte);
    if(flag_1 || flag_2 || flag_3){
      blockSize = loop_aux->lastByte - loop_aux->firstByte +1;
      if(flag_1){
        if(loop_aux == l2->head && l2->listSize != 0){
          //Caso 1.1: nodo a liberar esta en la cabeza.
          aux = l2->head;
          l2->head = aux->next;
          l2->listSize--;
          insert(l1,aux->firstByte,aux->lastByte,optiPos(l1,aux->firstByte,aux->lastByte));
          free(aux);
          fprintf(wp,"El bloque de %d bytes liberado.\n",blockSize);
          merge(l1);
          return;
        }
        if (loop_aux == l2->tail){
          //Caso 1.2 : nodo al liberar esta en la cola.
          prevNode->next = loop_aux->next;
          l2->tail = prevNode;
          l2->listSize--;
          aux = loop_aux;
          insert(l1,loop_aux->firstByte,loop_aux->lastByte,optiPos(l1,loop_aux->firstByte,loop_aux->lastByte));
          free(aux);
          fprintf(wp,"El bloque de %d bytes liberado.\n",blockSize);
          merge(l1);
          return;
        }
        else{
          //Caso 1.3: nodo a liberar esta entre la cabeza y la cola.
          aux = loop_aux;
          insert(l1,loop_aux->firstByte,loop_aux->lastByte,optiPos(l1,aux->firstByte,aux->lastByte));
          prevNode->next = loop_aux->next;
          loop_aux = loop_aux->next->next;
          l2->listSize--;
          free(aux);
          fprintf(wp,"El bloque de %d bytes liberado.\n",blockSize);
          merge(l1);
          return;
        }
      }
      if(flag_2){
        //Caso 2.1: byte inicial este en un nodo, pero dentro de sus limites.
        blockSize = loop_aux->lastByte - fbyte + 1;
        splitAndAdjust(l1,loop_aux,fbyte);
        fprintf(wp,"El bloque de %d bytes liberado.\n",blockSize);
        merge(l1);
        return;
      }
      if(flag_3){
        //Caso 3.1 : byte esta en el limite superior del bloque, no tiene bloque propio.
        printf("Free sin efecto.\n");
        return;
      }
    }
    if(auxCount >= 1){
      prevNode = prevNode->next;
    }
    auxCount++;
    loop_aux = loop_aux->next;
  }
}

/*************************************************************************************************
*void splitAndAdjust                                                                             *
**************************************************************************************************
*Se actualiza el nodo Node en la lista 2 y se agrega la parte del Nodo de la lista 2 (antes de)  *
*actualizar a la lista 1, asi "liberando" la memoria a partir de byte freeByte hasta el lastByte *
*de nodo separado.                                                                               *
**************************************************************************************************
*Input:  tLista *l1 - punero a la lista con memoria libre.                                       *
*        tNode *Node - puntero a un nodo a "separar".                                            *
*        int freeByte - byte, a partir del cual se hace el free.                                 *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void splitAndAdjust(tLista *l1, tNode *Node, int freeByte){
  int upperBound = Node->lastByte;
  insert(l1, freeByte, upperBound, optiPos(l1, freeByte, upperBound));
  Node->lastByte = freeByte - 1;
}

/*************************************************************************************************
*double dist                                                                                     *
**************************************************************************************************
*Calcula la distancia entre los dos nodos, usando la idea de distancia euclidiana. Por el alto   *
*costo de la funcion raiz, se la omite, obteniendo asi el cuadrado de la distancia real.         *
**************************************************************************************************
*Input:  int x1 - primer byte de nodo 1.                                                         *
*        int x2 - ultimo byte de nodo 1.                                                         *
*        int y1 - primer byte de nodo 2.                                                         *
*        int y2 - ultimo byte de nodo 2.                                                         *
**************************************************************************************************
*Returns: tipo double, distancia (sin aplicar la raiz) entre dos puntos en plano cartesiano.     *
**************************************************************************************************/

double dist(int x1, int x2, int y1, int y2){
  double dx = x1 - y2;
  double dy = y1 - x2;
  return dx * dx + dy * dy;
}

/*************************************************************************************************
*int optiPos                                                                                     *
**************************************************************************************************
*Encuentra la posicion optima para insertar un nodo en la lista con memoria libre. Se basa en la *
*funcion dist, que retorna la distancia al cuadrado entre un par de nodos. Se recorre la lista,  *
*analizando cada par de nodos y si este esta a la distancia minima, se guarda el puntero al nodo *
*de la lista 1 encontrado.                                                                       *
*Si este nodo tiene primer byte menor que firstByte, se inserta despues de el. Si no, en su pos, *
*desplazandolo a la derecha. En caso de que la lista este vacia, se inserta en posicion 0.       *
**************************************************************************************************
*Input: tLista *lista - puntero a lista con memoria libre.                                       *
*       int firstByte - primer byte del bloque a insertar.                                       *
*       int lastByte - ultimo byte del bloque a insertar.                                        *
**************************************************************************************************
*Returns: int loop_auxPos,mejor posicion para la insercion.                                      *
**************************************************************************************************/
int optiPos(tLista *lista, int firstByte, int lastByte){
  int minDist = INFINITY;
  int pos = 0;
  int loop_auxPos = 0;
  int distance = 0;
  tNode *loop_aux,*aux;
  loop_aux = lista->head;
  if(loop_aux == NULL){
    return 0;
  }
  while(loop_aux != NULL){
    distance = dist(firstByte, lastByte, loop_aux->firstByte, loop_aux->lastByte);
    if (distance < minDist){
      minDist = distance;
      aux = loop_aux;
      loop_auxPos = pos;
    }
    loop_aux = loop_aux->next;
    pos++;
  }
  if(firstByte < aux->firstByte){
    return loop_auxPos;
  }
  if(firstByte > aux->firstByte){
    return loop_auxPos+1;
  }
  return 0;
}

/*************************************************************************************************
*void merge                                                                                     *
**************************************************************************************************
*Recorre una lista,hasta encontrar un par de nodos contiguos (con la diferencia entre ultimo byte*
*de primer nodo y primer byte del segundo nodo igual a 1). Al encontrar tales nodos, se borra uno*
*y actualiza el segundo de modo que este tendra primer byte igual al primer byte de nodo borrado.*
*Al terminar el proceso, se reinicia el loop para revisar nuevos posibles pares de nodos a unir. *
**************************************************************************************************
*Input: tLista *lista - puntero a un contenedor de la enlazada.                                  *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void merge(tLista *lista){
  tNode *loop_aux, *prevNode;
  loop_aux = lista->head;
  if (loop_aux == NULL){
    return;
  }
  int pos = 0;
  prevNode = lista->head;
  loop_aux= loop_aux->next;
  while(loop_aux != NULL){
    if(loop_aux->firstByte - prevNode->lastByte == 1){ //son contiguos.
        loop_aux->firstByte = prevNode->firstByte;
        prevNode = prevNode->next;
        removeFromAvailable(lista,pos);
        prevNode = lista->head;
        pos = 0;
        loop_aux = lista->head;
        loop_aux = loop_aux->next;
      }
      else{
        pos++;
        prevNode = prevNode->next;
        loop_aux = loop_aux->next;
      }
    }
}

/*************************************************************************************************
*void append                                                                                     *
**************************************************************************************************
*Inserta un nuevo nodo  en la cola de la lista.                                                  *
**************************************************************************************************
*Input: tLista *lista - puntero a un contenedor de la enlazada.                                  *
*        int fbyte - primer byte de nodo.                                                        *
*        int lbyte - ultimo byte de nodo.                                                        *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void append(tLista *lista, int fbyte, int lbyte){
  tNode *aux = (tNode*)malloc(sizeof(tNode));
  aux->firstByte = fbyte;
  aux->lastByte = lbyte;
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

/*************************************************************************************************
*void insert                                                                                     *
**************************************************************************************************
*Inserta un elemento en la posicion dada. En caso de que la lista este vacia o se debe insertar  *
*al final de este, se llama a la funcion append. En caso de que se tiene que insertar en la      *
*cabeza de la lista no vacia, se crea un nodo y se lo enlaza antes de la cabeza. En otro caso, se*
*recorre la enlazada hasta la posicion pos-1, insertando el nodo entre los dos nodos en pos-1 y  *
*pos + 1;                                                                                        *
**************************************************************************************************
*Input: tLista *lista - puntero a un contenedor de la enlazada.                                  *
*        int fbyte - primer byte de nodo.                                                        *
*        int lbyte - ultimo byte de nodo.                                                        *
*        int pos - posicion para la insercion.                                                   *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void insert(tLista *lista, int fbyte, int lbyte, int pos){
  //Caso 1. Lista vacia.
  if (pos == 0 && lista->listSize == 0){
    append(lista, fbyte, lbyte);
    return;
  }
  //Caso 2. Insertar al final de la lista.
  if(pos ==  lista->listSize){
    append(lista, fbyte, lbyte);
    return;
  }
  tNode *aux = (tNode*)malloc(sizeof(tNode));
  aux->firstByte = fbyte;
  aux->lastByte = lbyte;
  //Caso 3. Insertar al inicio de la lista no vacia.
  if(pos == 0 && lista->listSize != 0){
    aux->next = lista->head;
    lista->head = aux;
    lista->listSize ++;
  }
  //Caso 4. Insertar en la posicion que no corresponde al extremo de la lista.
  else{
    if (pos > lista->listSize-1){
      return;
    }
    int k;
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

/*************************************************************************************************
*Se inicializa dos listas enlazadas y se abre el archivo de lectura. Ademas, se crea un archivo  *
*de escritura. Al leer el archivo INPUT_ARCHIVE, si la linea contiene un string de largo 6, este *
*corresponde al string Malloc y se ejecuta la funcion de asignacion de la memoria, basada en el  *
*algoritmo FirstFit. En caso de que el string tenga largo 4, se llama a la funcion newFree la    *
*cual es un analogo a la funcion free() de C. Las funciones FirstFit y newFree reciben el puntero*
*al archivo de escritura, de modo que se registra en este cualquier asignacion o liberacion de la*
*memoria.                                                                                        *
**************************************************************************************************/

#define INPUT_ARCHIVE "input1.dat"
#define OUTPUT_ARCHIVE "output1.txt"

int main(){
  tLista *l1 = initialize();
  tLista *l2 = initialize();

  int M, m, n;
  char command[6];

  FILE *fp,*wp;
  fp = fopen(INPUT_ARCHIVE, "r");
  if (fp == NULL){
    printf("Error en la apertura del archivo.\n");
    exit(1);
  }

  wp = fopen(OUTPUT_ARCHIVE, "w");
  if (wp == NULL){
    printf("Error en la apertura del archivo.\n");
    exit(1);
  }
  fscanf(fp, "%d", &M);
  insert(l1, 1, M, 0);
  fscanf(fp, "%d", &n);
  while(n > 0){
    fscanf(fp, "%s %d", command, &m);
    if(strlen(command) == 6){
      //m - size de memoria
      FirstFit(l1, l2, m, wp);
      /*
      //Visualizacion de las listas:
      printf("L1: ");
      printout(l1);
      printf("L2: ");
      printout(l2);
      printf("\n");
      */
    }
    if(strlen(command) == 4){
      //m - byte inicial a borrar
      newFree(l1,l2,m,wp);
      /*
      //Visualizacion de las listas:
      printf("L1: ");
      printout(l1);
      printf("L2: ");
      printout(l2);
      printf("\n");
      */
    }
    n--;
  }
  clear(l1);
  clear(l2);
  destroy(l1);
  destroy(l2);
  fclose(fp);
  fclose(wp);
  return 0;
}

/*************************************************************************************************
*void initialize                                                                                 *
**************************************************************************************************
*Inicializa la lista enlazada con su cabeza, actual y cola apuntando a NULL.                     *
**************************************************************************************************
*Input: sin input.                                                                               *
**************************************************************************************************
*Returns: tLista* lista, retorna un puntero  a un contenedor de una enlazada.                    *
**************************************************************************************************/

tLista* initialize(){
  tLista* lista = (tLista*)malloc(sizeof(tLista));
  lista->head = NULL;
  lista->tail = NULL;
  lista->curr = NULL;
  lista->listSize = 0;
  lista->currpos = 0;
  return lista;
}

/*************************************************************************************************
*void clear                                                                                 *
**************************************************************************************************
*Borra los nodos de la enlazada, dejandola vacia. Se borra desde el inicio, avanzando la cabeza  *
*hacia la cola. Una vez la cabeza pasa a ser NULL, se termina la funcion.                        *                                                 *
**************************************************************************************************
*Input: tLista *lista - un puntero a un contenedor de la enlazada.                               *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void clear(tLista *lista){
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

/*************************************************************************************************
*void destroy                                                                                    *
**************************************************************************************************
*Borra el contenedor del la enlazada.                                                            *
**************************************************************************************************
*Input:  tLista *lista - un puntero a la lista enlazada.                                         *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void destroy(tLista *lista){
  free((void*)lista);
}

/*************************************************************************************************
*void printout                                                                                    *
**************************************************************************************************
*Imprime la lista de forma ()->()->...->NULL                                                                  *
**************************************************************************************************
*Input:  tLista *lista - un puntero a la lista enlazada.                                         *
**************************************************************************************************
*Returns: no tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void printout(tLista *lista){
  if (lista->listSize == 0){
    printf("{}\n");
    return;
  }
  tNode *aux;
  aux = lista->head;
  while (aux != NULL){
    printf("(%d,%d)->", aux->firstByte, aux->lastByte);
    aux = aux->next;
  }
  printf("NULL\n");
}