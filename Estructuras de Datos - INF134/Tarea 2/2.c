#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************************************************
*Declaracion de la estructura de arbol.                                                          *
*Cada nodo almacena un puntero a su hijo derecho y izquierdo. Ademas, cada nodo contiene la      *
*informacion sobre la cantidad de nodos en su subarbol derecho (rightST) y izquierdo (leftST).   *
**************************************************************************************************/

typedef int tElemABB;

typedef struct nodeABB{
	tElemABB elem;
  	struct nodeABB *right;
  	struct nodeABB *left;
  	int leftST;
  	int rightST;
}tNodeABB;

typedef struct {
  	tNodeABB *root;
  	int lSubTree;
  	int rSubTree;
}tABB;

#define INPUT_ARCHIVE "input2.dat"
#define OUTPUT_ARCHIVE "output2.txt"


/*************************************************************************************************
*Declaraciones de las funciones utilizadas.                                                      *
**************************************************************************************************/

void destroy(tABB *Tree);
void initialize(tABB *Tree);
void clearAux(tNodeABB *Node);
void clear(tABB *Tree);
int existsAux(tNodeABB *Node, tElemABB item);
int exists(tABB *Tree, tElemABB item);
void insertAux(tNodeABB *Node, tElemABB item, tNodeABB *newNode, tABB *Tree);
void insert(tABB *Tree, tElemABB item);
void rankAux(tNodeABB *Node, tElemABB item, int *rank);
int rank(tABB *Tree, tElemABB item);

/*************************************************************************************************
*Se inicializa el arbol y se abre el archivo de lectura. Ademas, se crea un archivo de escritura. *
*Al leer el archivo INPUT_ARCHIVE, si la linea contiene un string de largo 6, este corresponde al *
*string Insert y se ejecuta la funcion de insercion. En caso de que el string tenga largo 4 - Rank*
*y se ejecuta la escritura del archivo wp, donde cada linea corresponde al rank de algun elemento.*
**************************************************************************************************/

int main(){
	tABB *Tree = (tABB*)malloc(sizeof(tABB));
  	char command[7];
  	int item;
  	initialize(Tree);
  	FILE *fp, *wp;

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

  	while (fscanf (fp, "%s %d", command, &item) != EOF){
    	if (strlen(command) == 6){
      		insert(Tree,item);
    	}
    	if (strlen(command) == 4){
      		fprintf(wp, "%d\n", rank(Tree, item));
    	}
  	}
  	fclose(wp);
  	fclose(fp);
  	clear(Tree);
  	destroy(Tree);
    return 0;
}

/*************************************************************************************************
*void initialize                                                                                 *
**************************************************************************************************
*Inicializa un arbol a partir de su nodo raiz.                                                   *
**************************************************************************************************
*Input: tABB *Tree : Un puntero al nodo-raiz de tipo tABB.                                       *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void initialize(tABB *Tree){
  	Tree->root = NULL;
  	Tree->rSubTree=Tree->lSubTree = 0;
}

/*************************************************************************************************
*void clearAux                                                                                   *
**************************************************************************************************
*De forma recursiva llama al hijo izquierdo y derecho del nodo a borrar.De modo que el borado se *
*hace desde las hojas hacia la raiz (en postorden).                                              *
**************************************************************************************************
*Input: tNodeABB *Node : Recibe un puntero a un nodo a borrar.                                   *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void clearAux(tNodeABB *Node){
  	if (Node == NULL){
    	return;
  }
  	clearAux(Node->left);
  	clearAux(Node->right);
  	free((void*)Node);
}

/*************************************************************************************************
*void clear                                                                                      *
**************************************************************************************************
*LLama a la funcion recursiva clearAux() con el puntero al nodo- raiz de tipo tNodeABB. Se tiene *
*que utilizar una funcion aparte dado que a partir de nodo-raiz no se puede crear una funcion    *
*recursiva, porque el nodo-raiz es el unico nodo de arbol de tipo tABB y no tNodeABB.            *
**************************************************************************************************
*Input: tABB *Tree : Un puntero a un nodo-raiz del arbol de tipo tABB.                           *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void clear(tABB *Tree){
  clearAux(Tree->root);
  Tree->root = NULL;
}

/*************************************************************************************************
int existsAux                                                                                    *
**************************************************************************************************
*Funcion de busqueda de un nodo particular. Recorre recursivamente el arbol, usando las          *
*propiedades de un arbol binario. Es decir,que la busqueda continua a la derecha si el item      *
*buscado es mayor que el nodo analizado y a la izquierda en caso contrario. La funcion para al   *
*encontrar un nood buscado o al llegar hasta la hoja ya visitada sin el siguiente hijo.          *
**************************************************************************************************
*Input: tElemABB item : Item buscado                                                             *
        tNodeABB *Node : Un puntero al nodo analizado                                            *
**************************************************************************************************
*Returns: int, 1 si el elemento esta en el arbol y 0 si no esta.                                 *
**************************************************************************************************/

int existsAux(tNodeABB *Node, tElemABB item){
  	if (Node == NULL){
    	return 0;
  	}
  	if (Node->elem == item){
    	return 1;
  	}
  	if (item < Node->elem){
    	return existsAux(Node->left, item);
  	}
  	if (item > Node->elem){
    	return existsAux(Node->right, item);
  	}
  	return -1;
}

/*************************************************************************************************
int exists                                                                                       *
**************************************************************************************************
*Funcion de busqueda de un nodo particular. Llama a una funcion recursiva existsAux que recorre  *
*el arbol binario buscando el nodo, cuyo elemento sea igual al buscado.                          *
**************************************************************************************************
*Input: tElemABB item : Item buscado                                                             *
        tABB *Tree : Un puntero al nodo-raiz del arbol.                                          *
**************************************************************************************************
*Returns: int, 1 si el elemento esta en el arbol y 0 si no esta.                                 *
**************************************************************************************************/

int exists(tABB *Tree, tElemABB item){
  	return existsAux(Tree->root, item);
}


/*************************************************************************************************
*void insertAux                                                                                  *
**************************************************************************************************
*Inserta un elemento al arbol, manteniendo su forma ABB. Si el item es menor que el elemento de  *
*nodo, se aumenta la cantidad de nodos del subarbol izquierdo del nodo analizado y se continua   *
*el intento a insetar el nodo a la izquierda, llamando la funcion de forma recursiva con el      *
*siguiente hijo izquierdo. Analogicamente, para la condicion de item mayor que el                 *
*elemento a insertar, con el cambio de camino hacia la derecha. Cuando ya no se puede seguir mas,*
*se enlaza el nodo newNode al arbol. Ademas, se aumenta la cantidad de nodos de subarbol de la   *
*raiz correspondiente al subarbol de insercion.                                                  *
**************************************************************************************************
*Input: tElemABB item : Item buscado.                                                            *
        tNodeABB *Node : Un puntero al nodo a analizar.                                          *
        tNodeABB *newNode : Un nuevo nodo creado para enlazar.                                    *
        tABB *Tree : Un puntero al nodo-raiz del arbol.                                          *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void insertAux(tNodeABB *Node, tElemABB item, tNodeABB *newNode, tABB *Tree){
  	if (item < Node->elem){
    	if (Node->left != NULL){
      		Node->leftST++;
      		insertAux(Node->left, item, newNode, Tree);
    	}
	else{
      	Node->left = newNode;
      	Node->leftST++;
      	Tree->lSubTree ++;
      	return;
    }
  	}	
  	if (item > Node->elem){
    	if (Node->right !=NULL){
      		Node->rightST++;
      		insertAux(Node->right, item, newNode, Tree);
    	}	
    	else{
      		Node->right = newNode;
      		Node->rightST++;
      		Tree->rSubTree ++;
      		return;
    	}	
  	}
}

/*************************************************************************************************
*void insert                                                                                     *
**************************************************************************************************
*Inicializa un nuevo nodo a insertar y llama a la funcion de insercion auxiliar insertAux.       *
*En caso que el arbol este vacio, se inicializa la raiz.                                         *
**************************************************************************************************
*Input: tElemABB item : item buscado.                                                            *
        tABB *Tree : Un puntero al nodo-raiz del arbol.                                          *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void insert(tABB *Tree, tElemABB item){
  	if (!exists(Tree, item)){ // solo si item no esta en arbol
    	tNodeABB *newNode = (tNodeABB*)malloc(sizeof(tNodeABB));
    	newNode->elem = item;
    	newNode->right = NULL;
    	newNode->left = NULL;
    	newNode->rightST = 1;
    	newNode->leftST = 1;

    	if (Tree->lSubTree+Tree->rSubTree == 0){ //caso de arbol vacio
      		Tree->root = newNode;
      		Tree->lSubTree = Tree->rSubTree = 1;
    	}
    	else{
      		insertAux(Tree->root, item, newNode, Tree);
    	}
  	}
}

/*************************************************************************************************
*void rankAux                                                                                    *
**************************************************************************************************
*La funcion se basa en que los nodos contienen la informacion sobre el size de su subarbol izq.  *
*Si el item a analizar es mayor que el elemento del nodo,tenemos que seguir buscando los nodos   *
*menores o iguales al elemento de forma recursiva.Si el elemento del nodo es menor o igual al    *
*item y ademas, el nodo tiene el siguiente hijo, entonces al rank le sumamos el tamano del       *
*subarbol izquierdo y seguimos a la derecha. Se suma el tamano de subarbol izquierdo dado que si *
*el item es mayor que el nodo, es mayor que cualquier nodo a su izquierda. Se sigue la busqueda  *
*hasta llegar a un nodo hoja y no poder seguir.La complejidad del algoritmo es O(logn) promedio y*
*O(h) en el peor caso, donde h es la altura del arbol.                                           *
**************************************************************************************************
*Input: tNodeABB *Node : Un puntero al nodo a analizar.                                          *
        tElemABB item : Un elemento cuyo rank se busca.                                          *
        int *rank : Un puntero al entero rank a calcular.                                        *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void rankAux(tNodeABB *Node, tElemABB item, int *rank){
  	if (Node == NULL){
    	return;
  	}
  	if (item < Node->elem){
    	if (Node->left == NULL){
      		return;
    	}
    	else{
      		Node = Node->left;
      		rankAux(Node, item, rank);
      		return;
    	}
  	}
  	if (item > Node->elem || item == Node->elem){
    	if (Node->right == NULL){
      		*rank +=  Node->leftST;
      		return;
    	}
    	else{
      		*rank +=  Node->leftST;
      		Node = Node->right;
      		rankAux(Node, item, rank);
      		return;
    	}
  	}
}

/*************************************************************************************************
*int rank                                                                                        *
**************************************************************************************************
*Inicializa el rank a retornar y llama a la funcion auxilar recursiva rankAux que lo calcula.    *
**************************************************************************************************
*Input:   tABB *Tree - Un puntero al nodo-raiz del arbol.                                        *
          tElemABB item - Un elemento cuyo rank se busca.                                        *
**************************************************************************************************
*Returns: int rank, rank del elemento de interes.                                                *
**************************************************************************************************/

int rank(tABB *Tree, tElemABB item){
  	int rank = 0;
  	rankAux(Tree->root, item, &rank);
  	return rank;
}

/*************************************************************************************************
*void destroy                                                                                    *
**************************************************************************************************
*Borra el contenedor del arbol.                                                                  *
**************************************************************************************************
*Input:  tABB *Tree : Un puntero al nodo-raiz del arbol.                                         *
**************************************************************************************************
*Returns: No tiene retorno, tipo void.                                                           *
**************************************************************************************************/

void destroy(tABB *Tree){
  	free(Tree);
}