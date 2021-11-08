#include <stdio.h>
#include <stdlib.h>

/* Funciones a tener:
- initialize() - inicializa un arbol;
- tElemTree getValue(tNodeTree *Node) - retorna valor de elem en nodo;
- void setValue(tNodeTree *Node,tElemTree item) - almacena un valor enc campo elem de nodo;
- tNodeTree *firstChild(tNodeTree *Node) - obtiene primer hijo de nodo;
- tNodeTree *nextSibling(tNodeTree *Node) - obtiene al siguiente hermano de nodo;
*/

typedef int tElemTree;

typedef struct nodeTree{
  tElemTree elem;
  nodeTree *child;
  nodeTree *sibling;
}tNodeTree;

tNodeTree initialize(tNodeTree *FirtsNode){
  *FirtsNode = (tNodeTree*)malloc(sizeof(tElemTree));
  *FirtsNode->child = NULL;
  *FirtsNode->sibling = NULL;
  return FirtsNode;
}

tElemTree getValue(tNodeTree *Node){
  return Node->elem;
}

void setValue(tNodeTree *Node,tElemTree item){
  Node->elem = item;
}

tNodeTree *firstChild(tNodeTree *Nodo){
  return Nodo->child;
}

tNodeTree *nextSibling(tNodeTree *Nodo){
  return Nodo->sibling;
}
