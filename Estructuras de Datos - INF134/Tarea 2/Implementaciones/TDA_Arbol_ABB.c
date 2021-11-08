#include <stdio.h>
#include <stdlib.h>

/*Funcion de Arbol Binario de Busqueda:
- void initialize(tABB *Tree) - incializa un arbol vacio
- void clear(tABB *Tree) - borra los contenidos de arbol,dejandolo vacio
- void destroy(tABB *Tree) - borra el arbol
- void insert(tABB *Tree,tElemABB item) - inserta un elemento en ABB
- remove (tABB *Tree,tElemABB item) - elimina de ABB
- int exists(tABB *Tree, tElemABB item) -retorna 0 si item no esta en arbol.
- tNodeABB* find (tABB *Tree,tElemABB item) - retorna el nodo de valor item
- int size(tABB *Tree) - retorna la cantidad de nodos de arbol
- void preOrden (tABB *Tree) - recorrido PLR
- void inOrden (tABB *Tree) - recorrido LPR
- void postOrden (tABB *Tree) - recorrido LRP
- void printout(tABB *Tree) - imprime al arbol
*/

typedef int tElemABB;

typedef struct nodeABB{
  tElemABB elem;
  struct nodeABB *right;
  struct nodeABB *left;
}tNodeABB;

typedef struct {
  tNodeABB *root;
  int numElem;
}tABB;


/*******************************************************************************
*Inicializa el arbol ABB.                                                      *
*******************************************************************************/

void initialize(tABB *Tree){
  Tree->root = NULL;
  Tree->numElem = 0;
}

/*******************************************************************************
*Funcion de busqueda. Esta separada en dos dado que recursivamente no podemos  *
*llamar con tNodeABB en una sola funcion, ya que solo la raiz tiene este tipo  *
*pero nos interesan los nodos,que tienen tipo tNodeABB.                        *
*Retorna 1 si el elemento esta en el arbol y 0 si no esta.                  *
*******************************************************************************/

int existsAux(tNodeABB *Node, tElemABB item){
  if (Node == NULL){
    return 0;
  }
  if (Node->elem == item){
    return 1;
  }
  if (item < Node->elem){
    return existsAux(Node->left,item);
  }
  if (item > Node->elem){
    return existsAux(Node->right,item);
  }
  return -1;
}

int exists(tABB *Tree,tElemABB item){
  return existsAux(Tree->root,item);
}

/*******************************************************************************
*Retorna la cantidad de nodos de ABB.                                          *
*******************************************************************************/


tNodeABB *findAux(tNodeABB *Node, tElemABB item){
  if (Node == NULL){
    return NULL;
  }
  if (Node->elem == item){
    return Node;
  }
  if (item < Node->elem){
    return findAux(Node->left,item);
  }
  if (item > Node->elem){
    return findAux(Node->right,item);
  }
  return NULL;
}

tNodeABB *find(tABB *Tree,tElemABB item){
  return findAux(Tree->root,item);
}

/*******************************************************************************
*Retorna la cantidad de nodos de ABB.                                          *
*******************************************************************************/

int size(tABB *Tree){
  return Tree->numElem;
}

/*******************************************************************************
*Inserta un elemento,manteniendo forma de ABB. Tiene dos funciones porque se   *
*tiene que llamar de forma recursiva los nodos.                                *
*Recordar que camino a la izquierda es para nodos de menor valor que el padre  *
*y a la derecha - de mayor valor que el padre.                                 *
*******************************************************************************/

void insertAux(tNodeABB *Node,tElemABB item,tNodeABB *newNode){
  if (item < Node->elem){
    if (Node->left != NULL){
      insertAux(Node->left,item,newNode);
    }
    else{
      Node->left = newNode;
    }
  }
  if (item > Node->elem){
    if (Node->right !=NULL){
      insertAux(Node->right,item,newNode);
    }
    else{
      Node->right = newNode;
    }
  }
}

void insert(tABB *Tree, tElemABB item){
  if (!exists(Tree,item)){ // solo si item no esta en arbol
    tNodeABB *newNode = (tNodeABB*)malloc(sizeof(tNodeABB));
    newNode->elem = item;
    newNode->right = newNode->left = NULL;
    if (Tree->numElem == 0){ //caso de arbol vacio
      Tree->root = newNode;
      Tree->numElem++;
    }
    else{
      insertAux(Tree->root,item,newNode);
    }
  }
}

/*******************************************************************************
*Recorrido pre-orden PLR - process left right                                  *
*******************************************************************************/
void preOrdenAux(tNodeABB *Node){
  if (Node == NULL){
    return;
  }
  printf("%d \n",Node->elem); //puede ser push al stack.
  preOrdenAux(Node->left);
  preOrdenAux(Node->right);

}
void preOrden(tABB *Tree){
  preOrdenAux(Tree->root);
}

/*******************************************************************************
*Recorrido in-orden LPR - left process right                                   *
*******************************************************************************/
void inOrdenAux(tNodeABB *Node){
  if (Node == NULL){
    return;
  }
  inOrdenAux(Node->left);
  printf("%d \n",Node->elem); //puede ser push al stack.
  inOrdenAux(Node->right);

}
void inOrden(tABB *Tree){
  inOrdenAux(Tree->root);
}
/*******************************************************************************
*Recorrido in-orden LRP -left right process                                    *
*******************************************************************************/
void postOrdenAux(tNodeABB *Node){
  if (Node == NULL){
    return;
  }
  postOrdenAux(Node->left);
  postOrdenAux(Node->right);
  printf("%d \n",Node->elem); //puede ser push al stack.

}
void postOrden(tABB *Tree){
  postOrdenAux(Tree->root);
}

tElemABB findMinAux(tNodeABB *Node,tElemABB min){
  if(Node != NULL){
  findMinAux(Node->left,min); //checks nodes inorder.
  if (Node->elem < min){
    min = Node->elem;
  }
  findMinAux(Node->right,min);
  }
  return min;
}

tElemABB findMin(tABB *Tree,tElemABB item){
  tNodeABB *aux = find(Tree,item);
  tElemABB min = aux->elem;
  return findMinAux(aux->right,min); //nos interesa el minimo de subarbol derecho
}

/*******************************************************************************
*Borra un elemento del arbol, manteniendo su orden ABB.                        *
*******************************************************************************/
/*
void remov(tABB *Tree,tElemABB item){
  tNodeABB *aux, *paux, *temp;
  if (exists(Tree,item)){ //solo si item esta en arbol
    aux = find(Tree,item);
    paux = parent(aux,item);
    if (aux->left == NULL && aux->right == NULL){ //caso 1: nodo hoja.
      if (paux == NULL){ //unica hoja es la raiz, cual no tiene padre.
        free(Tree->root);
      }
      if (paux->left == aux){
        paux->left = NULL;
      }
      if(paux->right == aux){
        paux->right = NULL;
      }
      free(aux);
      return;
    }
    if (aux->left !=NULL && aux->right != NULL){ //caso dos hijos
      temp = find(Tree,findMin(Tree,item));
      aux-> elem = temp->elem;
      free(temp);
    }
    if (aux->left !=NULL || aux->right != NULL){ //caso un hijo
      if (aux->left !=NULL){
        temp =  aux->left;
        free(aux);
        aux = aux->left;
      }
      else{
        temp =  aux->right;
        free(aux);
        aux = aux->right;
      }
    }
  }
}
*/
/*******************************************************************************
*Borra los contenidos del arbol.                                               *
*******************************************************************************/

void clearAux(tNodeABB *Node){
  if (Node == NULL){
    return;
  }
  clearAux(Node->left);
  clearAux(Node->right);
  free((void*)Node);
}

void clear(tABB *Tree){
  clearAux(Tree->root);
  Tree->numElem = 0;
  Tree->root = NULL;
}

/*******************************************************************************
*Borra el contenedor del arbol.                                                *
*******************************************************************************/

void destroy(tABB *Tree){
  free(Tree);
}

/*******************************************************************************
*                                   *                                          *
*******************************************************************************/
int main(void){
  tABB *Tree = (tABB*)malloc(sizeof(tABB));
  initialize(Tree);
  insert(Tree,20);
  insert(Tree,1);
  insert(Tree,9);
  insert(Tree,11);
  insert(Tree,42);
  insert(Tree,5);
  printf("%d\n",exists(Tree,9)); //1
  printf("%d\n",exists(Tree,1)); //1
  printf("%d\n",exists(Tree,20)); //1
  printf("%d\n",exists(Tree,15)); //0
  clear(Tree);
  destroy(Tree);
}
