#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/****************************************************************************************************
* Declaracion de constantes para los archivos.                                                      *
* La constante THRESHOLD corresponde al factor de carga maximo permitido.                           *
****************************************************************************************************/

#define ARCH_PROD "productos.dat"
#define ARCH_OFERTA "ofertas.dat"
#define ARCH_COMPRAS "compras.txt"
#define ARCH_BOLETA "boletas1.txt"
#define THRESHOLD 70

/****************************************************************************************************
* Buenos size para tablas de hashing.                                                               *
* Notar que todos los numeros presentados son primos, y cada uno es casi el doble de su predecesor  *
* Asi, podemos "duplicar" el size de tabla al hacer el rehashing.Ademas, cada numero esta lo mas    *
* lejos posible de la mas cercana a el potencia de 2.                                               *
****************************************************************************************************/

int primes[] = {11,23,53,97,193,389,769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};

/****************************************************************************************************
* Declaracion de plantilla de funcion, que retrorna el tamano de cualquier arreglo pasado a esta.   *
****************************************************************************************************/

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))

/****************************************************************************************************
* Structs base, que representan los productos en venta y las ofertas.                               *
****************************************************************************************************/

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

/****************************************************************************************************
* Nuevo struct, que se ocupa para HTListaDeCompras, donde cada nodo existente indica la frecuencia  *
* de compra de cierto producto por un cliente x.                                                    *
****************************************************************************************************/

typedef struct{
  int cod_producto;
  int total;
}itemAComprar;

/****************************************************************************************************
* structuras, usadas como ranuras, que almacenan registros en una HT especifica.                    *
* ada estructura contiene un puntero a registro de tipo correspondiente y un flag, que puede ser    *
* gual a 1 o a 0. 1 - ranura llena, 0 - ranura vacia. Notar que no se ocupara flag = 2 asumiendo    *
* ue el usuario nunca va a requerir borrar algo de HT, sino que solo va a actualizar los precios    *
*  ofertas a traves de la insercion de nuevo struct con el codigo, que ya existe en HT, para solo   *
* ctualizar los datos.                                                                              *
****************************************************************************************************/

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

/****************************************************************************************************
* Declaraciones de estructuras, que representan las 3 tablas de hashing cerrado implementadas.      *
* Cada struct almacena el tamano de la tabla y la cantidad de elementos, insertados en esta.        *
* Se llama a estos structs para obtener el factor de carga de cada HT. Y, ademas, el ht-> se ocupa  *
* cada vez, que se requiere recorrer una HT especifica.                                             *
****************************************************************************************************/

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

/****************************************************************************************************
* Prototipos de las funciones utilizadas.                                                           *
****************************************************************************************************/

void rehashProd(itemHTproducto **array, HTproducto *ht);
void rehashOfe(itemHToferta **array, HToferta*ht);
void rehashCompra(itemHTListaDeCompras **array, HTListaDeCompras *ht);
void insertHTprod(itemHTproducto **array, producto *p, HTproducto *ht);
void insertHTofe(itemHToferta **array, oferta *p, HToferta *ht);
void insertHTcompra(itemHTListaDeCompras **array, itemAComprar *p, HTListaDeCompras *ht);
itemHTproducto *initHTproducto(HTproducto *ht);
itemHToferta *initHToferta(HToferta *ht);
itemHTListaDeCompras *initHTCompras(HTListaDeCompras *ht);
int findPrimeSize(int n);
int hash1(const uint8_t* key, size_t length);
int hash2(int key,int m);
int pDouble(int i, int key,int m);
int load(int n, int m);
void clearOFE(itemHToferta *array, HToferta *ht);
void clearPROD(itemHTproducto *array, HTproducto *ht);
void clearCOMP(itemHTListaDeCompras *array, HTListaDeCompras *ht);
void destroyOFE(itemHToferta *array);
void destroyPROD(itemHTproducto *array);
void destroyCOMP(itemHTListaDeCompras *array);
void destroyHTprod(HTproducto *ht);
void destroyHTofe(HToferta *ht);
void destroyHTComp(HTListaDeCompras *ht);
int new(itemHTListaDeCompras *array, int m, int key);
int escribirArchivo(int *array, int size, itemHTListaDeCompras *htCompras, itemHToferta *htOferta, itemHTproducto *htProducto, HTproducto *p, HToferta *o, HTListaDeCompras *l);

/**************************************************************************************************
* itemHTproducto *initHTproducto                                                                  *
***************************************************************************************************
* Inicializa un array base de hash table, para poder almacenar los registros.                     *
***************************************************************************************************
* Input: HTproducto *ht - un puntero a la estructura base de hash table, que almacena su tamano y *
* la cantidad actual de ranuras llenas.                                                           *
***************************************************************************************************
* Returns: itemHTproducto, retorna un nuevo array base de hash table.                             *
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

/**************************************************************************************************
* itemHTListaDeCompras *initHTCompras                                                             *
***************************************************************************************************
* Inicializa un array base de hash table, para poder almacenar los registros.                     *
***************************************************************************************************
* Input: HTListaDeCompras *ht - un puntero a la estructura base de hash table, que almacena su    *
* tamano y la cantidad actual de ranuras llenas.                                                 *
***************************************************************************************************
* Returns: itemHTListaDeCompras, retorna un nuevo array base de hash table.                       *
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

/**************************************************************************************************
* itemHToferta *initHToferta                                                                      *
***************************************************************************************************
* Inicializa un array base de hash table, para poder almacenar los registros.                     *
***************************************************************************************************
* Input: HToferta *ht - un puntero a la estructura base de hash table, que almacena su  tamano y  *
* la cantidad actual de ranuras llenas.                                                           *
***************************************************************************************************
* Returns: itemHToferta, retorna un nuevo array base de hash table.                               *
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

/**************************************************************************************************
* int findPrimeSize                                                                               *
***************************************************************************************************
* Retorna el siguiente primo, mayor al dado, segun el orden del array global primos[]             *
***************************************************************************************************
* Input: un entero primo n                                                                        *
***************************************************************************************************
* Returns: retorna el siguiente entero, que sirvira como un nuevo tamano primo de la tabla de hash*
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

/**************************************************************************************************
* int hash1                                                                                       *
***************************************************************************************************
* Calcula, usando la llave, pasada a la funcion, valor de su posion en HT. La funcion usada       *
* corresponde al Jerkin's One At A Time hash.                                                     *
***************************************************************************************************
* Input: una llave como puntero de tipo uint8_t, y un size de la tabla analizada de tipo size_t.  *
***************************************************************************************************
* Returns: retorna una nueva posicion para insercion, un entero.                                  *
**************************************************************************************************/

int hash1(const uint8_t* key, size_t length){
  size_t i = 0;
  int hash = 0;
  while (i != (sizeof(int)/sizeof(uint8_t))){
    hash += key[i++];
    hash += hash << 1;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;                                                                                         
  hash += hash << 15;
  return hash % length;

}

/**************************************************************************************************
* int hash2                                                                                       *
***************************************************************************************************
* Calcula, usando la llave, pasada a la funcion, valor de su posicion en HT.                      *
* Se usa cuando hash1 produce colision.                                                           *
***************************************************************************************************
* Input: una llave key, un entero.                                                                *
***************************************************************************************************
* Returns: retorna una nueva posicion para insercion, un entero.                                  *
**************************************************************************************************/

int hash2(int key, int m){
  if(key%m != 0){
    return key % m;
  }
  else{
    return 1;
  }
}

/**************************************************************************************************
* int pDouble                                                                                     *
***************************************************************************************************
* Funcion de double hashing, que retorna el nuevo valor de posicion, para insercion en HT.        *
***************************************************************************************************
* Input: un entero i, contador de cuantas veces se habia desplazado la llave y una llave          *
* a insertar, un entero key.                                                                      *
***************************************************************************************************
* Returns: retorna una nueva posicion para insercion, un entero.                                  *
**************************************************************************************************/

int pDouble(int i, int key, int m){
  return i*hash2(key, m);
}

/**************************************************************************************************
* int load                                                                                        *
***************************************************************************************************
* Calcula el factor de carga de la tabla HT en porcentaje, de 0 a 100.                            *
***************************************************************************************************
* Input: un entero n, que representa la cantidad insertada de registros y un entero m, tamano de  *
* HT analizada.                                                                                   *
***************************************************************************************************
* Returns: retorna el factor de carga, en porcentaje, de 0 a 100.                                 *
**************************************************************************************************/

int load(int n, int m){
  return n*100/m;
}

/**************************************************************************************************
* void insertHTprod                                                                               *
***************************************************************************************************
* Chequea si producto existe en itemHTproducto, si no lo hace, lo anade                           *
***************************************************************************************************
* Input: un doble puntero a array-base de HT de tipo itemHTproducto, un puntero al registro a     *
* insertar, y un puntero a la tabla HT que contiene el tamano de este y la cantidad de ranuras,   *
* ya existentes.                                                                                  *
***************************************************************************************************
* Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void insertHTprod(itemHTproducto **array, producto *p, HTproducto *ht){
  int hashIndex;
  hashIndex = hash1((uint8_t*)&p->cod_producto,(size_t)ht->size);
  int i;
  int pos = hashIndex;
  for(i = 1;(*array)[pos].data != NULL && (*array)[pos].data->cod_producto != p->cod_producto;i++){
    pos = (hashIndex + pDouble(i,p->cod_producto,ht->size)) % ht->size;
  }
  if((*array)[pos].data != NULL && (*array)[pos].data->cod_producto == p->cod_producto){
    (*array)[pos].data->cod_producto = p->cod_producto;
    strcpy((*array)[pos].data->nbre_producto,p->nbre_producto);
    (*array)[pos].data->precio = p->precio;
    return;
  }
  else{
    producto *new_item = (producto*)malloc(sizeof(producto));
    new_item->cod_producto = p->cod_producto;
    strcpy(new_item->nbre_producto ,p->nbre_producto);
    new_item->precio = p->precio;
    (*array)[pos].flag = 1;
    (*array)[pos].data = new_item;
    ht->total++;
    if(load(ht->total,ht->size) > THRESHOLD){
      rehashProd(array,ht);
      return;
    }
  }
}

/**************************************************************************************************
* void insertHTcompra                                                                             *
***************************************************************************************************
* Dependiendo de si item existe o no en la lista de compras que se esta creando, se anadira a     *
* esta o se sumara +1 a las veces que aparece el item.                                            *
***************************************************************************************************
* Input: un doble puntero a array-base de HT de tipo itemHTListaDeCompras, un puntero al registro *
* a insertar, y un puntero a la tabla HT que contiene el tamano de este y la cantidad de ranuras, *
* ya existentes.                                                                                  *
***************************************************************************************************
* Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void insertHTcompra(itemHTListaDeCompras **array, itemAComprar *p, HTListaDeCompras *ht){
  int hashIndex;
  hashIndex = hash1((uint8_t*)&p->cod_producto, (size_t)ht->size);
  int i;
  int pos = hashIndex;
  for(i = 1; (*array)[pos].data != NULL && (*array)[pos].data->cod_producto != p->cod_producto; i++){
    pos = (hashIndex + pDouble(i, p->cod_producto,ht->size)) % ht->size;
  }
  if((*array)[pos].data != NULL && (*array)[pos].data->cod_producto == p->cod_producto){
    (*array)[pos].data->total = (*array)[pos].data->total + 1;
    return;
  }
  else{
    itemAComprar *new_item = (itemAComprar*)malloc(sizeof(itemAComprar));
    new_item->cod_producto = p->cod_producto;
    new_item->total = p->total;
    (*array)[pos].flag = 1;
    (*array)[pos].data = new_item;
    ht->total++;
    if(load(ht->total,ht->size) > THRESHOLD){
      rehashCompra(array,ht);
      return;
    }
  }
}

/**************************************************************************************************
* void insertHTofe                                                                                *
***************************************************************************************************
* Si ya hay una oferta existente para el mismo producto, la sobre escribe, si no existe otra      *
* igual, la anade.                                                                                *
***************************************************************************************************
* Input: un doble puntero a array-base de HT de tipo itemHToferta, un puntero al registro a       *
* insertar, y un puntero a la tabla HT que contiene el tamano de este y la cantidad de ranuras,   *
* ya existentes.                                                                                  *
***************************************************************************************************
* Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void insertHTofe(itemHToferta **array, oferta *p, HToferta *ht){
  int hashIndex;
  hashIndex = hash1((uint8_t*)&p->cod_producto,(size_t)ht->size);
  int i;
  int pos = hashIndex;
  for(i = 1; (*array)[pos].data != NULL && (*array)[pos].data->cod_producto != p->cod_producto; i++){
    pos = (hashIndex + pDouble(i,p->cod_producto,ht->size)) % ht->size;
  }
  if((*array)[pos].data != NULL && (*array)[pos].data->cod_producto == p->cod_producto){
    (*array)[pos].data->cantidad_descuento = p->cantidad_descuento;
    (*array)[pos].data->cod_producto = p->cod_producto;
    (*array)[pos].data->descuento = p->descuento;
    return;
  }
  else{
   oferta *new_item = (oferta*)malloc(sizeof(oferta));
   new_item->cantidad_descuento = p->cantidad_descuento;
   new_item->cod_producto = p->cod_producto;
   new_item->descuento = p->descuento;
   (*array)[pos].flag = 1;
   (*array)[pos].data = new_item;
   ht->total++;
   if(load(ht->total,ht->size) > THRESHOLD){
     rehashOfe(array,ht);
      return;
    }
  }
}

/**************************************************************************************************
* void rehashProd                                                                                 *
***************************************************************************************************
* Hace un nuevo hash, con mas espacio y pasa la informacion del hash viejo al nuevo.              *
***************************************************************************************************
* Input: un doble puntero a array-base de HT de tipo itemHTproducto, y un puntero a la tabla HT   *
* que contiene el tamano de este y la cantidad de ranuras, ya existentes.                         *
***************************************************************************************************
* Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void rehashProd(itemHTproducto **array, HTproducto *ht){
  int newSize = findPrimeSize(ht->size);
  int oldSize = ht->size;
  int i;
  ht->size = newSize;
  itemHTproducto *newHT = (itemHTproducto*)malloc(sizeof(itemHTproducto)*newSize);
  for(i = 0; i < newSize; i++){
    newHT[i].data = NULL;
    newHT[i].flag = 0;
  }
  ht->total = 0;
  for(i = 0; i < oldSize ; i++){
    if((*array)[i].data != NULL){
      insertHTprod(&newHT, (*array)[i].data, ht);
    }
  }
  ht->size = oldSize;
  clearPROD(*array, ht);
  destroyPROD(*array);
  ht->size =  newSize;
  *array = newHT;
}

/*************************************************************************************************
* void rehashCompra                                                                              *
**************************************************************************************************
* Hace un nuevo hash, con mas espacio y pasa la informacion del hash viejo al nuevo.             *
**************************************************************************************************
*Input: Un doble puntero a array-base itemHTListaDeCompras, y un puntero a la tabla 			 *
*HTListaDeCompras, la cual contiene la informacion de esta.  									 *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void rehashCompra(itemHTListaDeCompras **array, HTListaDeCompras *ht){
  int newSize = findPrimeSize(ht->size);
  int oldSize = ht->size;
  int i;
  ht->size = newSize;
  itemHTListaDeCompras *newHT = (itemHTListaDeCompras*)malloc(sizeof(itemHTListaDeCompras)*newSize);
  for(i = 0; i < newSize; i++){
    newHT[i].data = NULL;
    newHT[i].flag = 0;
  }
  ht->total = 0;
  for(i = 0; i < oldSize ; i++){
    if((*array)[i].data != NULL){
      insertHTcompra(&newHT, (*array)[i].data, ht);
    }
  }
  ht->size = oldSize;
  clearCOMP(*array, ht);
  destroyCOMP(*array);
  ht->size =  newSize;
  *array = newHT;
}

/*************************************************************************************************
*void rehashOfe                                                                                  *
**************************************************************************************************
* Hace un nuevo hash, con mas espacio y pasa la informacion del hash viejo al nuevo.             *
**************************************************************************************************
*Input: Un doble puntero a HToferta , y un puntero a la tabla HToferta, la cual contiene la      *
informacion de esta.																			 *
**************************************************************************************************
*Returns: tipo void, sin retorno.                                                                *
**************************************************************************************************/

void rehashOfe(itemHToferta **array, HToferta *ht){
  int newSize = findPrimeSize(ht->size);
  int oldSize = ht->size;
  int i;
  ht->size = newSize;
  itemHToferta *newHT = (itemHToferta*)malloc(sizeof(itemHToferta)*newSize);
  for(i = 0; i < newSize; i++){
    newHT[i].data = NULL;
    newHT[i].flag = 0;
  }
  ht->total = 0;
  for(i = 0; i < oldSize ; i++){
    if((*array)[i].data != NULL){
      insertHTofe(&newHT, (*array)[i].data, ht);
    }
  }
  ht->size = oldSize;
  clearOFE(*array, ht);
  destroyOFE(*array);
  ht->size = newSize;
  *array =  newHT;
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

void clearOFE(itemHToferta *array, HToferta *ht){
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

void clearPROD(itemHTproducto *array, HTproducto *ht){
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

void clearCOMP(itemHTListaDeCompras *array, HTListaDeCompras *ht){
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
*Input: puntero  a la tabla HT de tipo itemHTproducto.                                           *                                         
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

int new(itemHTListaDeCompras *array, int m, int key){
  int hashIndex;
  hashIndex = hash1((uint8_t*)&key, (size_t)m);
  int pos;
  pos = hashIndex;
  int i = 0;
  while (array[pos].flag != 0){
    if(array[pos].flag == 1 && array[pos].data->cod_producto == key ){
      return 1;
    }
    i++;
    pos = (hashIndex + pDouble(i, key, m)) % m;
  }
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

int escribirArchivo(int *array, int size, itemHTListaDeCompras *htCompras, itemHToferta *htOferta, itemHTproducto *htProducto, HTproducto *p, HToferta *o, HTListaDeCompras *l){
  int i;
  int hashIndex1, hashIndex2, hashIndex3;
  int total = 0;
  int partialSum = 0;
  int pos1, pos2, pos3;
  int precioNormal = 0;
  int cantidad = 0;
  int cantiDescu = 1;
  int descuento = 0;
  int m1, m2, m3;

  for(i = 0; i < size; i++){
    hashIndex1 = hash1((uint8_t*)&array[i], (size_t)p->size);
    hashIndex2 = hash1((uint8_t*)&array[i], (size_t)o->size);
    hashIndex3 = hash1((uint8_t*)&array[i], (size_t)l->size);
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
    while(flag1 != 0 || flag2 != 0 || flag3 != 0){
      if(flag1 != 0){
        if(htProducto[pos1].data != NULL){
          if(htProducto[pos1].data->cod_producto == array[i]){
            flag1 = 0;
            precioNormal = htProducto[pos1].data->precio;
          }
          else{
            m1++;
            pos1 = (hashIndex1 + pDouble(m1, array[i], p->size)) % p->size;
            if(pos1 >= p->size){
              pos1 = pos1 % p->size;
            }
            if(pos1 == hashIndex1){
              flag1 = 0;
            }
          }
        }
        else{
          flag1 = 0;
          precioNormal = 0;
        }
      }
        if(flag2 != 0){
          if(htOferta[pos2].data != NULL){
            if(htOferta[pos2].data->cod_producto == array[i]){
              flag2 = 0;
              descuento =  htOferta[pos2].data->descuento;
              cantiDescu = htOferta[pos2].data->cantidad_descuento;
            }
            else{
              m2++;
              pos2 = (hashIndex2 + pDouble(m2, array[i], o->size)) % o->size;
              if(pos2 >= o->size){
                pos2 = pos2 % o->size;
              }
              if (pos2 == hashIndex2){
                flag2 = 0;
                cantiDescu = 1;
                descuento = 0;
              }
            }
        }
        else{
          flag2 = 0;
        }
      }
      if(flag3 != 0){
        if(htCompras[pos3].data != NULL){
          if(htCompras[pos3].data->cod_producto == array[i]){
            flag3 = 0;
            cantidad = htCompras[pos3].data->total;
          }
          else{
            m3++;
            pos3 = (hashIndex3 + pDouble(m3, array[i], l->size)) % l->size;
            if (pos3 == hashIndex3){
              flag3 = 0;
            }
          }
        }
        else{
            flag3 = 0;
        }
      }
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
*1.Leer el archivo binario ARCH_PROD                                                            *
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
  int aux, n;
  int sizeProd = 0;
  int countProd;
  int sizeOfer = 0;
  FILE *fp, *wp;
  producto *P;
  oferta *O;

  HTproducto *HTprod = (HTproducto*)malloc(sizeof(HTproducto));
  HToferta *HTofer = (HToferta*)malloc(sizeof(HToferta));

  fp = fopen(ARCH_PROD, "rb");
  aux = fread(&sizeProd, sizeof(int), 1, fp);

  if (aux != 1 ){
    printf("ERROR! No se pudo leer el archivo.\n");
    exit(1);
  }

  itemHTproducto *prod = initHTproducto(HTprod);
  P = (producto*)malloc(sizeof(producto) * sizeProd);
  aux = fread(P, sizeof(producto), sizeProd, fp);

  for(n = 0; n < sizeProd; n++){
    insertHTprod(&prod, (P + n), HTprod);
  }
  fclose(fp);

  fp = fopen(ARCH_OFERTA, "rb");
  aux = fread(&sizeOfer, sizeof(int), 1, fp);

  if (aux != 1 ){
    printf("ERROR! No se pudo leer el archivo.\n");
    exit(1);
  }

  itemHToferta *ofe = initHToferta(HTofer);
  O = (oferta*)malloc(sizeof(oferta) * sizeOfer);
  aux = fread(O, sizeof(oferta), sizeOfer, fp);

  for(n = 0; n < sizeOfer; n++){
    insertHTofe(&ofe, (O + n), HTofer);
  }

  free(O);
  free(P);
  fclose(fp);

  fp = fopen(ARCH_COMPRAS, "r");
  HTListaDeCompras *HTCompra = (HTListaDeCompras*)malloc(sizeof(HTListaDeCompras));
  itemHTListaDeCompras *comp = initHTCompras(HTCompra);

  itemAComprar *compra_aux = (itemAComprar*)malloc(sizeof(itemAComprar));
  compra_aux->total = 1;

  wp = fopen(ARCH_BOLETA, "w");
  if (wp == NULL){
    printf("Error en la apertura del archivo.\n");
    exit(1);
  }

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
      compra_aux->total = 1;
    }
    fprintf(wp, "%d", escribirArchivo(bucket, count, comp, ofe, prod, HTprod, HTofer, HTCompra));
    fputs("\n", wp);
    clearCOMP(comp, HTCompra);
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
