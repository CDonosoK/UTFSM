#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************************************************
*Declaracion de constantes para los archivos.                                                    *
*La constante THRESHOLD corresponde al factor de carga maximo permitido.                         *
**************************************************************************************************/

#define ARCH_PROD "productos.dat"
#define ARCH_OFERTA "ofertas.dat"
#define ARCH_COMPRAS "compras.txt"
#define ARCH_BOLETA "boletas.txt"
#define THRESHOLD 70

/*************************************************************************************************
*Buenos size para tablas de hashing.                                                             *
*Notar que todos los numeros presentados son primos, y cada uno es casi el doble de su predecesor*
*Asi, podemos "duplicar" el size de tabla al hacer el rehashing.Ademas, cada numero esta lo mas  *
*lejos posible de la mas cercana a el potencia de 2.                                             *
**************************************************************************************************/

int primes[] = {11,23, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

/*************************************************************************************************
*Declaracion de plantilla de funcion, que retrorna el tamano de cualquier arreglo pasado a esta. *
**************************************************************************************************/

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

/*************************************************************************************************
*Structs base, que representan los productos en venta y las ofertas.                             *
**************************************************************************************************/
typedef struct {
  int cod_producto;
  char nbre_producto[31];
  int precio;
}producto;

typedef struct {
  int cod_producto;
  int cantidad_descuento;
  int descuento;
}oferta;

/*************************************************************************************************
*Nuevo struct, que se ocupa para HTListaDeCompras, donde cada nodo existente indica la frecuencia*
*de compra de cierto producto por un cliente x.                                                  *
**************************************************************************************************/

typedef struct{
  int cod_producto;
  int total;
}itemAComprar;

/*************************************************************************************************
*Estructuras, usadas como ranuras, que almacenan registros en una HT especifica.                 *
*Cada estructura contiene un puntero a registro de tipo correspondiente y un flag, que puede ser *
*igual a 1 o a 0. 1 - ranura llena, 0 - ranura vacia. Notar que no se ocupara flag = 2 asumiendo *
*que el usuario nunca va a requerir borrar algo de HT, sino que solo va a actualizar los precios *
*u ofertas a traves de la insercion de nuevo struct con el codigo, que ya existe en HT,para solo *
*actualizar los datos.                                                                           *
**************************************************************************************************/

typedef struct {
  int flag;
  producto *data;
}itemHTproducto;

typedef struct {
  int flag;
  oferta *data;
}itemHToferta;

typedef struct {
  int flag;
  itemAComprar *data;
}itemHTListaDeCompras;

/*************************************************************************************************
*Declaraciones de estructuras, que representan las 3 tablas de hashing cerrado implementadas.    *
*Cada struct almacena el tamano de la tabla y la cantidad de elementos, insertados en esta.      *
*Se llama a estos structs para obtener el factor de carga de cada HT. Y, ademas, el ht-> se ocupa*
*cada vez, que se requiere recorrer una HT especifica.                                           *
**************************************************************************************************/

typedef struct{
  int total;
  int size;
}HTproducto;

typedef struct{
  int total;
  int size;
}HToferta;

typedef struct{
  int total;
  int size;
}HTListaDeCompras;

/*************************************************************************************************
*Prototipos de las funciones utilizadas.                                                         *
**************************************************************************************************/

void rehashProd(itemHTproducto **array, HTproducto *ht);
void rehashOfe(itemHToferta **array, HToferta*ht);
void rehashCompra(itemHTListaDeCompras **array, HTListaDeCompras *ht);
void insertHTprod(itemHTproducto **array, producto *p, HTproducto *ht);
void insertHTofe(itemHToferta **array, oferta *p, HToferta *ht);
void insertHTcompra(itemHTListaDeCompras **array, itemAComprar *p, HTListaDeCompras *ht);
itemHTproducto *initHTproducto(HTproducto *ht);
itemHToferta *initHToferta(HToferta *ht);
int findPrimeSize(int n);
int hash1(int key, int m);
int hash2(int key,int m);
int pDouble(int i, int key,int m);
int load(int n, int m);
void printoutPROD(itemHTproducto *array, HTproducto *ht);
void printoutOFE(itemHToferta *array, HToferta *ht);
void printoutCOMP(itemHTListaDeCompras *array, HTListaDeCompras *ht);
void clearOFE(itemHToferta *array, HToferta *ht);
void clearPROD(itemHTproducto *array, HTproducto *ht);
void destroyOFE(itemHToferta *array);
void clearCOMP(itemHTListaDeCompras *array, HTListaDeCompras *ht);
void destroyPROD(itemHTproducto *array);
void destroyCOMP(itemHTListaDeCompras *array);
void destroyHTprod(HTproducto *ht);
void destroyHTofe(HToferta *ht);
void destroyHTComp(HTListaDeCompras *ht);
itemHTListaDeCompras *initHTCompras(HTListaDeCompras *ht);
int new(itemHTListaDeCompras *array, int m, int key);
int escribirArchivo(int *array, int size, itemHTListaDeCompras *htCompras, itemHToferta *htOferta, itemHTproducto *htProducto, HTproducto *p, HToferta *o, HTListaDeCompras *l);

/*************************************************************************************************
*itemHTproducto *initHTproducto                                                                  *
**************************************************************************************************
*Inicializa un array base de hash table, para poder almacenar los registros.                     *
**************************************************************************************************
*Input: HTproducto *ht - un puntero a la estructura base de hash table, que almacena su tamano y *
*la cantidad actual de ranuras llenas.                                                           *
**************************************************************************************************
*Returns: itemHTproducto, retorna un nuevo array base de hash table.                             *
**************************************************************************************************/

itemHTproducto *initHTproducto(HTproducto *ht){
  int i;
  ht->size = primes[0];
  itemHTproducto *P = (itemHTproducto*)malloc(sizeof(itemHTproducto) * ht->size);
  if (P == NULL){
    printf("ERROR! No se pudo alocar la memoria.\n");
    exit(1);
  }
  for(i = 0; i < ht->size; i++){
      P[i].data = NULL;
      P[i].flag = 0;
  }
  ht->total = 0;
  return P;
}

/*************************************************************************************************
*itemHTListaDeCompras *initHTCompras                                                             *
**************************************************************************************************
*Inicializa un array base de hash table, para poder almacenar los registros.                     *
**************************************************************************************************
*Input: HTListaDeCompras *ht - un puntero a la estructura base de hash table, que almacena su    *
tamano y la cantidad actual de ranuras llenas.                                                   *
**************************************************************************************************
*Returns: itemHTListaDeCompras, retorna un nuevo array base de hash table.                       *
**************************************************************************************************/

itemHTListaDeCompras *initHTCompras(HTListaDeCompras *ht){
  int i;
  ht->size = primes[0];
  itemHTListaDeCompras *L = (itemHTListaDeCompras*)malloc(sizeof(itemHTListaDeCompras)*ht->size);
  if(L == NULL){
    printf("ERROR! No se pudo alocar la memoria.\n");
    exit(1);
  }
  for(i = 0; i < ht->size; i++){
      L[i].data = NULL;
      L[i].flag = 0;
  }
  ht->total = 0;
  return L;
}

/*************************************************************************************************
*itemHToferta *initHToferta                                                                      *
**************************************************************************************************
*Inicializa un array base de hash table, para poder almacenar los registros.                     *
**************************************************************************************************
*Input: HToferta *ht - un puntero a la estructura base de hash table, que almacena su  tamano y  *
la cantidad actual de ranuras llenas.                                                            *
**************************************************************************************************
*Returns: itemHToferta, retorna un nuevo array base de hash table.                               *
**************************************************************************************************/

itemHToferta *initHToferta(HToferta *ht){
  int i;
  ht->size = primes[0];
  itemHToferta *O = (itemHToferta*)malloc(sizeof(itemHToferta) * ht->size);
  for(i = 0; i < ht->size; i++){
    O[i].data = NULL;
    O[i].flag = 0;
  }
  ht->total = 0;
  return O;
}

/*************************************************************************************************
*int findPrimeSize                                                                               *
**************************************************************************************************
*Retorna el siguiente primo, mayor al dado, segun el orden del array global primos[]             *
**************************************************************************************************
*Input: un entero primo n                                                                        *
**************************************************************************************************
*Returns: retorna el siguiente entero, que sirvira como un nuevo tamano primo de la tabla de hash*
**************************************************************************************************/

int findPrimeSize(int n){
  int i;
  size_t m = NELEMS(primes);
  for(i = 0; i < (int)m; i++){
    if(primes[i] > n){
      return primes[i];
    }
  }
  return 0;
}

/*************************************************************************************************
*int hash1                                                                                       *
**************************************************************************************************
*Calcula, usando la llave, pasada a la funcion, valor de su posion en HT.                        *
**************************************************************************************************
*Input: una llave entera key, y un size entero, m, de la tabla analizada                         *
**************************************************************************************************
*Returns: retorna una nueva posicion para insercion, un entero.                                  *
**************************************************************************************************/

int hash1(int key, int m){
  return ((4 * key + 11) % 1610612741) % m ;
}

/*************************************************************************************************
*int hash2                                                                                       *
**************************************************************************************************
*Calcula, usando la llave, pasada a la funcion, valor de su posicion en HT. Se usa cuando hash1  *
*produce colision.                                                                               *
**************************************************************************************************
*Input: una llave key, un entero.                                                                *
**************************************************************************************************
*Returns: retorna una nueva posicion para insercion, un entero.                                  *
**************************************************************************************************/

int hash2(int key,int m){
  return ((2*key + 2)% 805306457) % m;
}

/*************************************************************************************************
*int pDouble                                                                                     *
**************************************************************************************************
*Funcion de double hashing,que retorna el nuevo valor de posicion, para insercion en HT.         *
**************************************************************************************************
*Input: un entero i, contador de cuantas veces se habia desplazado la llave y una llave          *
* a insertar, un entero key.                                                                     *
**************************************************************************************************
*Returns: retorna una nueva posicion para insercion, un entero.                                  *
**************************************************************************************************/

int pDouble(int i,int key,int m){
  return i*hash2(key,m);
}

/*************************************************************************************************
*int load                                                                                        *
**************************************************************************************************
*Calcula el factor de carga de la tabla HT en porcentaje, de 0 a 100.                            *
**************************************************************************************************
*Input: un entero n, que representa la cantidad insertada de registros y un entero m, tamano de  *
*HT analizada.                                                                                   *
**************************************************************************************************
*Returns: retorna el factor de carga, en porcentaje, de 0 a 100.                                 *
**************************************************************************************************/

int load(int n,int m){
  return n*100/m;
}

/*************************************************************************************************
*void insertHTprod                                                                               *
**************************************************************************************************
*
**************************************************************************************************
*Input: un doble puntero a array-base de HT de timo itemHTproducto,un puntero al registro a      *
*insertar, y un puntero a la tabla HT que contiene el tamano de este y la cantidad de ranuras,ya *
*existentes.                                                                                     *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void insertHTprod(itemHTproducto **array, producto *p, HTproducto *ht){
 printf("Procediendo a insertar (%d,%s,%d)\n",p->cod_producto,p->nbre_producto,p->precio );
  int hashIndex;
  hashIndex = hash1(p->cod_producto,ht->size);
  int i = 0;
  int pos = hashIndex;
  if (pos >= ht->size){
    pos = pos % ht->size;
  }
  //tenemos que encontrar una ranura con valor 0 :
  //Probamos de hash(key) =  hashIndex. Si no lo encuentra, aumentamos el desfase.
  while((*array)[pos].flag != 0){
    printf("Probando pos %d de llave %d\n",pos,p->cod_producto);
    //Caso 1. Ya existe una llave asi.Actualicemos.
    if((*array)[pos].flag == 1 && (*array)[pos].data->cod_producto == p->cod_producto){
     printf("\n\n Se repitio el codigo!!!!!!!\n" );
      (*array)[pos].data->cod_producto = p->cod_producto;
      strcpy((*array)[pos].data->nbre_producto,p->nbre_producto);
      (*array)[pos].data->precio = p->precio;

      printf("El registro (%d,%s,%d) fue insertado exitosamente en ranura %d.\n",p->cod_producto,p->nbre_producto,p->precio,pos);
      printoutPROD(*array,ht);
      return;
    }
    // aumentamos la posicion segund (hash(key) + p(key,i))%m
    printf("Ranura %d ocupada. Avanzando.\n",pos);
    i++;
    pos = (hashIndex + pDouble(i,p->cod_producto,ht->size)) % ht->size;
    if (pos >= ht->size){
      pos = pos % ht->size;
    }
    // Caso 2. Hicimos un loop completo sobre el array. No se encontro espacio vacio.
    if (pos == hashIndex){
//      printf("Tabla llena, no se puede insertar mas elementos.\n");
      return;
    }
  }
  // Caso 3. Se encontro un espacio para la insercion. Hay que crear nuevo registro.
  producto *new_item = (producto*)malloc(sizeof(producto));
  new_item->cod_producto = p->cod_producto;
  strcpy(new_item->nbre_producto ,p->nbre_producto);
  new_item->precio = p->precio;
  (*array)[pos].flag = 1;
  (*array)[pos].data = new_item;
 printf("El registro (%d,%s,%d) fue insertado exitosamente en ranura %d.\n",p->cod_producto,p->nbre_producto,p->precio,pos);
  ht->total++;
 printf("Load es: %d \n",load(ht->total,ht->size));
  if(load(ht->total,ht->size) > THRESHOLD){
    printf("El load es %d, mayor a threshold, hay que rehashear\n",load(ht->total,ht->size));
    rehashProd(array,ht);
    return;
  }
}

/*************************************************************************************************
*void insertHTcompra                                                                             *
**************************************************************************************************
*
**************************************************************************************************
*Input: un doble puntero a array-base de HT de timo itemHTListaDeCompras,un puntero al registro a*
*insertar, y un puntero a la tabla HT que contiene el tamano de este y la cantidad de ranuras,ya *
*existentes.                                                                                     *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void insertHTcompra(itemHTListaDeCompras **array,itemAComprar *p, HTListaDeCompras *ht){
  int hashIndex;
  hashIndex = hash1(p->cod_producto,ht->size);
  int i = 0;
  int pos = hashIndex;
  if (pos >= ht->size){
    pos = pos % ht->size;
  }
  while((*array)[pos].flag != 0){
//    printf("Probando pos %d de llave %d\n",pos,p->cod_producto );
    //Caso 1. Ya existe una llave asi.Tenemos que sumar la cantidad "total"
    if((*array)[pos].flag == 1 && (*array)[pos].data->cod_producto == p->cod_producto){
  //    printf("Llave %d ya existe en %d. El cliente repitio el producto. Sumamos.\n",p->cod_producto,pos);
      (*array)[pos].data->total++;
      return;
    }// aumentamos la posicion segund (hash(key) + p(key,i))%m
//    printf("Ranura %d ocupada. Avanzando.\n",pos);
    i++;
    pos = (hashIndex + pDouble(i,p->cod_producto,ht->size)) % ht->size;
    // Caso 2. Hicimos un loop completo sobre el array. No se encontro espacio vacio.
    if (pos >= ht->size){
      pos = pos % ht->size;
    }
    if (pos == hashIndex){
    //  printf("Tabla llena, no se puede insertar mas elementos.\n");
      return;
    }
  }
  // Caso 3. Se encontro un espacio para la insercion. Hay que crear nuevo registro.
  itemAComprar *new_item = (itemAComprar*)malloc(sizeof(itemAComprar));
  new_item->cod_producto = p->cod_producto;
  new_item->total = 1;
  (*array)[pos].flag = 1;
  (*array)[pos].data = new_item;
//  printf("El item con llave %d fue insertado exitosamente en ranura %d.\n",p->cod_producto,pos);
  ht->total++;
  if(load(ht->total,ht->size) > THRESHOLD){
    //printf("El load es %d, mayor a threshold, hay que rehashear\n",load(ht->total,ht->size));
    rehashCompra(array,ht);
    return;
  }
}

/*************************************************************************************************
*void insertHTofe                                                                                *
**************************************************************************************************
*
**************************************************************************************************
*Input: un doble puntero a array-base de HT de timo itemHToferta,un puntero al registro a        *
*insertar, y un puntero a la tabla HT que contiene el tamano de este y la cantidad de ranuras,ya *
*existentes.                                                                                     *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void insertHTofe(itemHToferta **array,oferta *p,HToferta *ht){
  printf("\nSe procede a insertar una oferta %d\n",p->cod_producto );
//  printoutOFE(*array,ht);
  int hashIndex;
  hashIndex = hash1(p->cod_producto,ht->size);
  int i = 0;
  int pos = hashIndex;
  printf("pos oferta: %d,ht size : %d\n",pos,ht->size );
  if (pos >= ht->size){
    pos = pos % ht->size;
  }
  //tenemos que encontrar una ranura con valor 0 :
  //Probamoa de hash(key) =  hashIndex. Si no lo encuentra, aumentamos el desfase.
  while((*array)[pos].flag != 0){
  printf("Probando pos %d de llave %d\n",pos,p->cod_producto );
    //Caso 1. Ya existe una llave asi.Actualicemos.
    if((*array[pos]).flag == 1){
      /*if((*array)[pos].data->cod_producto == p->cod_producto){
        printf("La llave %d ya existe en ranura %d. Haciendo update de su valor.\n",p->cod_producto,pos);
        (*array)[pos].data->cantidad_descuento = p->cantidad_descuento;
        (*array)[pos].data->cod_producto = p->cod_producto;
        (*array)[pos].data->descuento = p->descuento;
        return;
      }*/
    }
    // aumentamos la posicion segund (hash(key) + p(key,i))%m
  printf("Ranura %d ocupada. Avanzando.\n",pos);
    i++;
    pos = (hashIndex + pDouble(i,p->cod_producto,ht->size)) % ht->size;
    if (pos >= ht->size){
      pos = pos % ht->size;
    }
    // Caso 2. Hicimos un loop completo sobre el array. No se encontro espacio vacio.
    if (pos == hashIndex){
      //printf("Tabla llena, no se puede insertar mas elementos.\n");
      return;
    }
  }
  // Caso 3. Se encontro un espacio para la insercion. Hay que crear nuevo registro.
  oferta *new_item = (oferta*)malloc(sizeof(oferta));
  new_item->cantidad_descuento = p->cantidad_descuento;
  new_item->cod_producto = p->cod_producto;
  new_item->descuento = p->descuento;
  (*array)[pos].flag = 1;
  (*array)[pos].data = new_item;
  printf("El registro (%d,%d,%d) fue insertado exitosamente en ranura %d.\n",p->cantidad_descuento,p->cod_producto,p->descuento,pos);
  ht->total++;
  if(load(ht->total,ht->size) > THRESHOLD){
  //  printf("El load es %d, mayor a threshold, hay que rehashear\n",load(ht->total,ht->size));
    rehashOfe(array,ht);
    return;
  }
}

/*************************************************************************************************
*void rehashProd                                                                                 *
**************************************************************************************************
*
**************************************************************************************************
*Input:
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void rehashProd(itemHTproducto **array,HTproducto *ht){
  printf("Se llama de nuevo a rehashing de productos.\n");
  int newSize = findPrimeSize(ht->size);
  int oldSize = ht->size;
  int i;
  printf("nuevo tamano es: %d\n",newSize);
  ht->size = newSize;
  itemHTproducto *newHT = (itemHTproducto*)malloc(sizeof(itemHTproducto)*newSize);
  for(i = 0; i < newSize; i++){
    newHT[i].data = NULL;
    newHT[i].flag = 0;
  }
  printf("load factor final: %d\n",load(ht->total,ht->size) );
  //rehasheamos todo
  ht->total = 0;
  for(i = 0; i < oldSize ; i++){
    printf("I:%d\n",i );
    if((*array)[i].data != NULL){
      insertHTprod(&newHT,(*array)[i].data,ht);
    }
  }
  ht->size = oldSize;
  clearPROD(*array,ht);
  destroyPROD(*array);
  ht->size =  newSize;
  *array = newHT;
  printf("HASH PROD REHASHEADO!");
  printoutPROD(*array,ht);
}

/*************************************************************************************************
*int fload                                                                                       *
**************************************************************************************************
*
**************************************************************************************************
*Input:
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void rehashCompra(itemHTListaDeCompras **array,HTListaDeCompras *ht){
  printf("Se llama de nuevo a rehashing de productos.\n");
  int newSize = findPrimeSize(ht->size);
  int oldSize = ht->size;
  int i;
  printf("nuevo tamano es: %d\n",newSize);
  ht->size = newSize;
  itemHTListaDeCompras *newHT = (itemHTListaDeCompras*)malloc(sizeof(itemHTListaDeCompras)*newSize);
  for(i = 0; i < newSize; i++){
    newHT[i].data = NULL;
    newHT[i].flag = 0;
  }
  printf("load factor final: %d\n",load(ht->total,ht->size) );
  //rehasheamos todo
  ht->total = 0;
  for(i = 0; i < oldSize ; i++){
    printf("I:%d\n",i );
    if((*array)[i].data != NULL){
      insertHTcompra(&newHT,(*array)[i].data,ht);
    }
  }
  ht->size = oldSize;
  clearCOMP(*array,ht);
  destroyCOMP(*array);
  ht->size =  newSize;
  *array = newHT;
  printf("HASH COMPRA REHASHEADO!");
  printoutCOMP(*array,ht);
}

/*************************************************************************************************
*void rehashOfe                                                                                  *
**************************************************************************************************
*
**************************************************************************************************
*Input:
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void rehashOfe(itemHToferta **array,HToferta *ht){
  int newSize = findPrimeSize(ht->size);
  int oldSize = ht->size;
  int i;
  printf("nuevo tamano es: %d\n",newSize);
  ht->size = newSize;
  itemHToferta *newHT = (itemHToferta*)malloc(sizeof(itemHToferta)*newSize);
  for(i = 0; i < newSize; i++){
    newHT[i].data = NULL;
    newHT[i].flag = 0;
  }
  printf("load factor final: %d\n",load(ht->total,ht->size) );
  //rehasheamos todo
  ht->total = 0;
  for(i = 0; i < oldSize ; i++){
    printf("I:%d\n",i );
    if((*array)[i].data != NULL){
      printf("Producto %d no es NULL\n",(*array)[i].data->cod_producto);
      insertHTofe(&newHT,(*array)[i].data,ht);
    }
  }
  ht->size = oldSize;
  clearOFE(*array,ht);
  destroyOFE(*array);
  ht->size = newSize;
  *array =  newHT;
  printf("HASH OFE REHASHEADO!");
  printoutOFE(*array,ht);
}


void printoutPROD(itemHTproducto *array, HTproducto *ht){
  int i;
  printf("\n\n");
  printf("HASH TABLE PRODUCTOS:\n");
  printf("----------------\n");
  for (i = 0; i < ht->size; i++){
    if (array[i].data != NULL){
      if (array[i].flag == 1){
        printf("%d:(%s con codigo %d cuesta %d)\nEstado de ranura: %d\n",i,array[i].data->nbre_producto,array[i].data->cod_producto,array[i].data->precio,array[i].flag);
      }
    }
    else{
      if (array[i].flag == 0 ){
        printf("%d:NULL,estado %d\n",i,array[i].flag);
      }
    }
    printf("----------------\n");
  }
}


void printoutOFE(itemHToferta *array, HToferta *ht){
  int i;
  printf("\n\n");
  printf("HASH TABLE OFERTONES:\n");
  printf("----------------\n");
  for (i = 0; i < ht->size; i++){
    if (array[i].data != NULL){
      if (array[i].flag == 1){
        printf("%d:Oferta de codigo %d para %d unidades obtiene descuento de %d)\n Estado de ranura: %d\n",i,array[i].data->cod_producto,array[i].data->cantidad_descuento,array[i].data->descuento,array[i].flag);
      }
    }
    else{
      if (array[i].flag == 0 ){
        printf("%d:NULL,estado %d\n",i,array[i].flag);
      }
    }
    printf("----------------\n");
  }
}

void printoutCOMP(itemHTListaDeCompras *array, HTListaDeCompras *ht){
  int i;
  printf("\n\n");
  printf("HASH TABLE Compras:\n");
  printf("----------------\n");
  for (i = 0; i < ht->size; i++){
    if (array[i].data != NULL){
      if (array[i].flag == 1){
        printf("%d:Item de codigo %d en cantidad de %d\n",i,array[i].data->cod_producto,array[i].data->total);
      }
    }
    else{
      if (array[i].flag == 0 ){
        printf("%d:NULL,estado %d\n",i,array[i].flag);
      }
    }
    printf("----------------\n");
  }
}

/*************************************************************************************************
*void clearOFE                                                                                   *
**************************************************************************************************
*Libera las ranuras de HT.                                                                       *
**************************************************************************************************
*Input: puntero al array base de HT de tipo itemHToferta un puntero a la estructura,que          *
*almacena el tamano de HT y cantidad de ranuras llenas.                                          *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void clearOFE(itemHToferta *array,HToferta *ht){
  int i;
  for(i = 0; i < ht->size; i++){
    array[i].flag = 0;
    free(array[i].data);
    array[i].data = NULL;
  }
}

/*************************************************************************************************
*void clearPROD                                                                                  *
**************************************************************************************************
*Libera las ranuras de HT.                                                                       *
**************************************************************************************************
*Input: puntero al array base de HT de tipo itemHTproducto y un puntero a la estructura,que      *
*almacena el tamano de HT y cantidad de ranuras llenas.                                          *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void clearPROD(itemHTproducto *array,HTproducto *ht){
  int i;
  for(i = 0; i < ht->size; i++){
    array[i].flag = 0;
    free(array[i].data);
    array[i].data = NULL;
  }
}

/*************************************************************************************************
*void clearCOMP                                                                                  *
**************************************************************************************************
*Libera las ranuras de HT.                                                                       *
**************************************************************************************************
*Input: puntero al array base de HT de tipo itemHTListaDeCompras y un puntero a la estructura,que*
*almacena el tamano de HT y cantidad de ranuras llenas.                                          *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void clearCOMP(itemHTListaDeCompras *array,HTListaDeCompras *ht){
  int i;
  for(i = 0; i < ht->size; i++){
    array[i].flag = 0;
    free(array[i].data);
    array[i].data = NULL;
  }
}

/*************************************************************************************************
*void destroyOFE                                                                                 *
**************************************************************************************************
*Libera el array - base de la HT.                                                                *
**************************************************************************************************
*Input: puntero  a la tabla HT de tipo itemHToferta.                                             *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void destroyOFE(itemHToferta *array){
  free(array);
}

/*************************************************************************************************
*void destroyPROD                                                                                *
**************************************************************************************************
*Libera el array - base de la HT.                                                                *
**************************************************************************************************
*Input: puntero  a la tabla HT de tipo itemHTproducto.                                           *                                         **************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void destroyPROD(itemHTproducto *array){
  free(array);
}

/*************************************************************************************************
*void destroyCOMP                                                                                *
**************************************************************************************************
*Libera el array - base de la HT.                                                                *
**************************************************************************************************
*Input: puntero  a la tabla HT de tipo itemHTListaDeCompras.                                     *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void destroyCOMP(itemHTListaDeCompras *array){
  free(array);
}

/*************************************************************************************************
*void destroyHTprod                                                                              *
**************************************************************************************************
*Libera el puntero a struct de tipo HTproducto que contiene el tamano y la cantidad de           *
*ranuras llenas.                                                                                 *
**************************************************************************************************
*Input: puntero  a la tabla HT de tipo HTproducto.                                               *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void destroyHTprod(HTproducto *ht){
  free(ht);
}

/*************************************************************************************************
*void destroyHTofe                                                                               *
**************************************************************************************************
*Libera el puntero a struct de tipo HToferta que contiene el tamano y la cantidad de ranuras     * *llenas.                                                                                         *
**************************************************************************************************
*Input: puntero  a la tabla HT de tipo HToferta.                                                 *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void destroyHTofe(HToferta *ht){
  free(ht);
}

/*************************************************************************************************
*void destroyHTComp                                                                              *
**************************************************************************************************
*Libera el puntero a struct de tipo HTListaDeCompras que contiene el tamano y la cantidad de     *
*ranuras llenas.                                                                                 *
**************************************************************************************************
*Input: puntero  a la tabla HT de tipo HTListaDeCompras.                                         *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void destroyHTComp(HTListaDeCompras *ht){
  free(ht);
}

/*************************************************************************************************
*int new                                                                                         *
**************************************************************************************************
*Usando la politica de resolucion de colisiones y busqueda en HT, se revisa los nodos, hasta     *
*encontrar un nodo con la llave, que coincide con la que se pide analizar o, en cambio, al       *
*encontrar NULL en la primera ranura esperada, o, hasta hacer el loop entero sobre la tabla. En  *
*los dos ultimos casos se concluye que la llave no existe en la tabla y se retorna un -1.        *
**************************************************************************************************
*Input: un puntero a la tabla HT de tipo itemHTListaDeCompras, tamano de este y la llave, cuya   *
*existencia que se busca revisar.                                                                *
**************************************************************************************************
*Returns: -1 si el nodo no existe en la tabla y 1, si existe.                                    *
**************************************************************************************************/

int new(itemHTListaDeCompras *array, int m,int key){
  int hashIndex;
  hashIndex = hash1(key,m);
  int pos;
  pos = hashIndex;
  int i = 0;
  while (array[pos].flag != 0){
    if(array[pos].flag == 1 && array[pos].data->cod_producto == key ){
      printf("La llave %d fue encontrada en la ranura %d\n",key,pos);
      return 1;
    }
    i++;
    pos = (hashIndex + pDouble(i,key,m)) % m;
    //Si hicimos el loop completo:
    if (pos == hashIndex){
      printf("Elemento %d no esta en la tabla.\n",key);
      return -1;
    }
  }
  printf("Elemento %d no esta en la tabla.\n",key);
  return -1;
}

/*************************************************************************************************
*int escribirArchivo                                                                             *
**************************************************************************************************
*A la vez, se recorre las tres HT,la HT que tiene almacenadas las compras, HT con ofertas y HT   *
*productos en venta.                                                                             *
*Dado que usamos el mismo hashing para las tres HT, para no buscar por separado en cada tabla,   *
*usamos solo un while. Se usa 3 flags, para, una vez encontrado un nodo en una de las tablas,    *
*dejar de actualizar los valores, buscados en una de las tablas, Flag1 corresponde a HT de       *
*productos, Flag2 - a la HT de ofertas y Flag3 - a la tabla de compras de cliente. El loop       *
*termina, cuando se encuentra todos los datos buscados en las 3 tablas.                          *
*Una vez terminado el loop, se calcula el total de compra por cliente y se termina la ejecucion. *
**************************************************************************************************
*Input: un puntero al array auxiliar, que almcena las llaves de compras de cliente, punteros a   *
*las tablas HT de tipo itemAComprar,itemHToferta,itemHTListaDeCompras y sus estructuras          *
*complementarias de tipo HTproducto, HToferta, HTListaDeCompras, las cuales contienen los        *
*tamanos de sus HT correspondientes, y cantidad de ranuras llenas.                               *
**************************************************************************************************
*Returns: un entero, total de compra por un cliente.                                             *
**************************************************************************************************/

int escribirArchivo(int *array,int size,itemHTListaDeCompras *htCompras,itemHToferta *htOferta, itemHTproducto *htProducto,HTproducto *p,HToferta *o,HTListaDeCompras *l){
  printf("\n\nEMPEZANDO A ESCRIBIR ARCHIVO:\n");
  int i;
  int hashIndex1, hashIndex2, hashIndex3;
  int total = 0;
  int partialSum = 0;
  int pos1,pos2,pos3;
  int precioNormal = 0;
  int cantidad = 0;
  int cantiDescu = 1;
  int descuento = 0;
  int m1,m2,m3;

  for(i = 0; i < size; i++){
    printf("\nIndex %d, elemento %d\n",i,array[i] );
    hashIndex1 = hash1(array[i],p->size);
    hashIndex2 = hash1(array[i],o->size);
    hashIndex3 = hash1(array[i],l->size);
    printf("hash1:%d,hash2:%d,hash3:%d\n",hashIndex1,hashIndex2,hashIndex3 );
    pos1 = hashIndex1;
    if(pos1 >= p->size){
      pos1 = pos1 % p->size;
    }
    pos2 = hashIndex2;
    if(pos2 >= o->size){
      pos2 = pos2 % o->size;
    }
    pos3 = hashIndex3;
    if(pos3 >= l->size){
      pos3 = pos3 % l->size;
    }
    m1=m2=m3=0;
    int flag1 = htProducto[pos1].flag;
    int flag2 = htOferta[pos2].flag;
    int flag3 = htCompras[pos3].flag;
    printf("Analizando nuevo elemento %d de indice i = %d \nlag1:%d,flag2:%d,flag3:%d\n",array[i],i,flag1,flag2,flag3 );
    while(flag1 != 0 || flag2 != 0 || flag3 != 0){
      //Caso 1. Si todavia no se encontro el nodo de tipo producto:
      if(flag1 != 0){
        printf("En flag1:\n" );
        if(htProducto[pos1].data != NULL){
          printf("en flag1 no nulo:\n" );
          printf("Htproducto[pos1].data->codigo = %d\n",htProducto[pos1].data->cod_producto );
          if(htProducto[pos1].data->cod_producto == array[i]){
            flag1 = 0;
            precioNormal = htProducto[pos1].data->precio;
          }
          else{
            m1++;
            printf("m1: %d\n",m1 );
            pos1 = (hashIndex1 + pDouble(m1,array[i],p->size)) % p->size;
            if(pos1 >= p->size){
              pos1 = pos1 % p->size;
            }
            printf("nueva pos: %d\n",pos1 );
            printf("size de htProductos es: %d\n",p->size );
            if(pos1 == hashIndex1){
              printf("Tal producto no existe,pos1 == hashIndex1.");
              flag1 = 0;
            }
          }
        }
        //Si nodo en posicion esperada es NULL, el producto no existe.
        else{
          printf("Tal producto no existe,su ranura es NULL.");
          flag1 = 0;
          precioNormal = 0;
        }
      }
      //Caso 2. Si todavia no se encontro la oferta o no se verifico que esta no existe:
        if(flag2 != 0){
          printf("\nEn flag2\n" );
          if(htOferta[pos2].data != NULL){
            printf("En flag2 no nulo:\n" );
            if(htOferta[pos2].data->cod_producto == array[i]){
              flag2 = 0;
              descuento =  htOferta[pos2].data->descuento;
              cantiDescu = htOferta[pos2].data->cantidad_descuento;
              printf("Producto %d tiene descuento %d aplicable a %d unidades\n",array[i],descuento,cantiDescu );
            }
            else{
              m2++;
              printf("m2:%d\n",m2 );
              pos2 = (hashIndex2 + pDouble(m2,array[i],o->size)) % o->size;
              if(pos2 >= o->size){
                pos2 = pos2 % o->size;
              }
              printf("nueva pos2:%d\n",pos2 );
              if (pos2 == hashIndex2){
                printf("Producto %d no esta con oferta.\n",array[i]);
                flag2 = 0;
                cantiDescu = 1;
                descuento = 0;
              }
            }
        }
        else{
          printf("Producto %d no esta con oferta.\n",array[i]);
          flag2 = 0;
        }
      }
      //Caso 3. En busqueda de nodo de compra de cliente, para obtener el total de productos comprados.
      if(flag3 != 0){
        printf("En flag3,pos3 = %d\n",pos3);
        if(htCompras[pos3].data != NULL){
          printf("En flag3 no nulo,pos3:%d:\n",pos3);
          printf("pos3:%d\n",pos3 );
          printf("htCompras[pos3].data->cod_producto:%d\n",htCompras[pos3].data->cod_producto );
          if(htCompras[pos3].data->cod_producto == array[i]){
            flag3 = 0;
            cantidad = htCompras[pos3].data->total;
          }
          else{
            m3++;
            printf("m3:%d\n",m3 );
            pos3 = (hashIndex3 + pDouble(m3, array[i],l->size)) % l->size;
            if(pos3 >= l->size){
              pos3 = pos3 % l->size;
            }
            printf("Nueva pos3:%d \n",pos3 );
            if (pos3 == hashIndex3){
              printf("Producto %d no esta en lista de compras.\n",array[i]);
              flag3 = 0;
              printf("ERROR.\n");
            }
          }
        }
      }
      printf("No pudo ubicar la cosa en HT de compras...\n");
      flag3 = 0;
    }
    partialSum = precioNormal * cantidad - ((cantidad / cantiDescu) * descuento);
    total += partialSum;
    partialSum = 0;
    cantidad = 0;
    cantiDescu = 1;
    descuento = 0;
  }
  return total;
}

/*************************************************************************************************
*Algoritmo:                                                                                      *
*1. Leer el archivo binario ARCH_PROD                                                            *
*2.Guardar los contenidos en un array P de tipo producto.                                        *
*3.Insertar todos los structs de array a una HT de tipo itemHTproducto.                          *
*4.Analogicamente, para ARCH_OFERTA, guardando todo en array O de tipo oferta y escribiendo los  *
*structs en array de tipo itemHToferta.                                                          *
*                                                                                                *
*Una vez terminados los pasos mencionados, cerramos los archivos ARCH_PROD y ARCH_OFERTA.        *
*5. Leer el archivo ARCH_COMPRAS,guardando la primera linea en variable auxilar aux, que         *
*representa la cantidad de clientes. Ahora, para cada cliente, se crea un nodo temporal          *
*compra_aux, que se inserta a una HT de frecuencia de compra comp de tipo itemHTListaDeCompras.  *
*Ademas,para cada nodo insertado, se analiza si la clave de este todavia no existe en un array   *
*auxiliar bucket (de tamano 1.000.000,como este es el rango maximo de compra por cliente).Este   *
*array se utilizara despues para buscar las compras de cliente y la frecuencia de su compra.     *
*                                                                                                *
*Una vez analizadas las compras de un cliente,calculamos el total y lo escribimos en el archivo  *
*ARCH_BOLETA. Al terminar el proceso, avanzamos hacia el siguiente cliente, reiniciando tanto HT *
*de compras como el nodo temporal compra_aux.                                                    *
*                                                                                                *
*Al terminar el calculo para cada cleinte, cerramos el archivo ARCH_BOLETA y ARCH_COMPRAS.       *
*Liberamos el array auxiliar bucket, y las 3 HT utilizadas en el proceso.                        *
**************************************************************************************************/

int main(){
  int aux,n;
  int sizeProd = 0;
  int countProd;
  int sizeOfer = 0;
  FILE *fp,*wp;
  producto *P;
  oferta *O;

  //Contenedores, que se van a usar solo para analizar el factor de carga
  HTproducto *HTprod = (HTproducto*)malloc(sizeof(HTproducto));
  HToferta *HTofer = (HToferta*)malloc(sizeof(HToferta));

  fp = fopen(ARCH_PROD, "rb");
  aux = fread(&sizeProd, sizeof(int), 1, fp);
  printf("Size de productos:%d\n", sizeProd );

  if (aux != 1 ){
    printf("ERROR! No se pudo leer el archivo.\n");
    exit(1);
  }

  itemHTproducto *prod = initHTproducto(HTprod);
  P = (producto*)malloc(sizeof(producto) * sizeProd);
  aux = fread(P, sizeof(producto), sizeProd, fp);

  //Insercion en HT de productos
  for(n = 0; n < sizeProd; n++){
    insertHTprod(&prod, (P + n), HTprod);
  }
  fclose(fp);
  printf("Termine de hashear productos!\n");

  fp = fopen(ARCH_OFERTA, "rb");
  aux = fread(&sizeOfer, sizeof(int), 1, fp);
  printf("Size de ofertas:%d\n", sizeOfer );
  if (aux != 1 ){
    printf("ERROR! No se pudo leer el archivo.\n");
    exit(1);
  }

  itemHToferta *ofe = initHToferta(HTofer);
  O = (oferta*)malloc(sizeof(oferta) * sizeOfer);
  aux = fread(O, sizeof(oferta), sizeOfer, fp);

  //Insercion en HT de ofertas
  for(n = 0; n < sizeOfer; n++){
    insertHTofe(&ofe, (O + n), HTofer);
  }
  //borramos el contenedor inutil.

  printf("\n\n" );
  printoutPROD(prod,HTprod);
  printoutOFE(ofe,HTofer);


  free(O);
  free(P);
  fclose(fp);

  fp = fopen(ARCH_COMPRAS, "r");
  HTListaDeCompras *HTCompra = (HTListaDeCompras*)malloc(sizeof(HTListaDeCompras));
  itemHTListaDeCompras *comp = initHTCompras(HTCompra);
  //Nodo temporal de tipo itemAComprar.
  itemAComprar *compra_aux = (itemAComprar*)malloc(sizeof(itemAComprar));
  compra_aux->total = 0;

  wp = fopen(ARCH_BOLETA, "w");
  if (wp == NULL){
    printf("Error en la apertura del archivo.\n");
    exit(1);
  }
  //Aux representa la cantidad de clientes.
  fscanf(fp,"%d", &aux);
  fprintf(wp, "%d", aux);
  fputs("\n", wp);
  int count = 0;
  int *bucket = (int*)malloc(1000000*sizeof(int));
  memset(bucket, 0, 1000000);

  while(aux != 0){
    fscanf(fp, "%d", &countProd);
    while(countProd != 0){
      fscanf(fp, "%d", &(compra_aux->cod_producto));
      if(new(comp,HTCompra->size, compra_aux->cod_producto) == -1){
        bucket[count] = compra_aux->cod_producto;
        count++;
      }
      insertHTcompra(&comp, compra_aux, HTCompra);
      countProd--;
      compra_aux->total = 0;
    }
    printoutCOMP(comp, HTCompra);
    fprintf(wp, "%d", escribirArchivo(bucket, count, comp, ofe, prod, HTprod, HTofer, HTCompra));
    fputs("\n", wp);
    clearCOMP(comp,HTCompra);
    destroyCOMP(comp);
    comp = initHTCompras(HTCompra);
    count = 0;
    aux--;
  }
  free(compra_aux);
  fclose(wp);
  fclose(fp);
  free(bucket);
  clearOFE(ofe, HTofer);
  clearPROD(prod, HTprod);
  clearCOMP(comp, HTCompra);
  destroyOFE(ofe);
  destroyPROD(prod);
  destroyCOMP(comp);
  destroyHTofe(HTofer);
  destroyHTprod(HTprod);
  destroyHTComp(HTCompra);
  return 0;
}
