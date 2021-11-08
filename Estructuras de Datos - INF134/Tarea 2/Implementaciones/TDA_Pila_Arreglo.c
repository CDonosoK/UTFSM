#include <stdio.h>
#include <stdlib.h>

/* Tipo LIFO - last in first out
initialize() - inicializa la pila
push() - inserta un elemento en la cabeza
topValue() - retorna el ultimo elemento introducido
pop() - saca un elemento de la cabeza
size() - retorna el size de pila
*/

typedef int tElemStack;

#define MAXSIZE 5

typedef struct{
  tElemStack *stack_array;
  int bottom;
  int top;
  int maxSize;
  int stackSize;
}tStack;


/*******************************************************************************
*Inicializa el stack.                                                          *
*******************************************************************************/

tStack* initialize(){
  tStack *stack = malloc(sizeof(tStack));
  stack->stack_array = (tElemStack*)malloc(sizeof(tElemStack)*MAXSIZE);
  stack->maxSize = MAXSIZE;
  stack->bottom = -1;
  stack->top = -1;
  stack->stackSize = 0;
  return stack;
}

/*******************************************************************************
*Borra el stack y reinicializa este.                                           *
*******************************************************************************/

void clear(tStack *stack){
  free((void*)stack);
  initialize();
}

/*******************************************************************************
*Retorna el ultimo valor introducido.                                          *
*******************************************************************************/

tElemStack topValue(tStack *stack){
  return stack->stack_array[stack->top];
}

/*******************************************************************************
*Inserta un item en la parte superio (tail)                                    *
*******************************************************************************/

int push(tStack *stack,tElemStack item){
  if (stack->top == -1){ //stack vacio
    stack->top = stack->bottom = 0;
    stack->stack_array[0] = item;
  }
  else if(stack->top == stack->maxSize-1){
    return -1; // no se puede insertar mas
  }
  else{
    stack->top++;
    stack->stack_array[stack->top] = item;
  }
  stack->stackSize ++;
  return 1; // push exitoso
}

/*******************************************************************************
*Retorna la cantidad de elementos en stack.                                    *
*******************************************************************************/

int size(tStack *stack){
  return stack->stackSize;
}

/*******************************************************************************
*Saca el ultimo elemento introducido.                                          *
*******************************************************************************/

int pop(tStack *stack){
  // si esta vacia, no se puede sacar nada.
  if (stack->stackSize == 0){
    return -1;
  }
  //mueve el "puntero" de posicion hacia abajo
  stack->top--;
  stack->stackSize--;
  return 1; //pop exitoso
}

/*******************************************************************************
*Imprime la pila.                                                              *
*******************************************************************************/
void printout(tStack *stack){
  if (stack-> stackSize == 0){
    printf("Stack vacio!\n");
    return;
  }
  else{
    printf("STACK\n");
    printf("___________\n" );
    for(int i = stack->top; i >= 0;i--){
      printf("|%10d|\n",stack->stack_array[i]);
      printf("___________\n" );
    }
    printf("END OF STACK\n");

  }
}

/*******************************************************************************
*Borra el stack contenedor.                                                    *
*******************************************************************************/
void destroy(tStack *stack){
  free((void*)stack);

}

/*******************************************************************************
*                                   *                                          *
*******************************************************************************/

int main(void){
  tStack *stack = initialize();
  printf("size:%d\n",size(stack)); //size:0
  printout(stack); //Stack vacio!

  push(stack,1);
  push(stack,200);
  push(stack,9);
  push(stack,19);
  push(stack,11);
  printout(stack);

/*
  STACK
  ___________
  |        11|
  ___________
  |        19|
  ___________
  |         9|
  ___________
  |       200|
  ___________
  |         1|
  ___________
  END OF STACK*/

  printf("size:%d\n",size(stack)); //5
  printf("\n" );
  pop(stack);
  printout(stack);

/*STACK
  ___________
  |        19|
  ___________
  |         9|
  ___________
  |       200|
  ___________
  |         1|
  ___________
  END OF STACK*/

  printf("size:%d\n",size(stack));//4
  clear(stack);
  destroy(stack);
}
