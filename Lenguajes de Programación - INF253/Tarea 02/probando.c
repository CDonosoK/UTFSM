#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "lista.c"
// su ejecutable se llama "plass"
#define ENTERO 0
#define FLOTANTE 1
#define ABRIRLISTA 2

/*typedef struct dato {
    void *contenido ;
    char tipo ;
} dato;*/

int identificacion (char pal[100]){
    int h = 0;
    if (pal[0]=='['){
        return 2;
    }
    else if (pal[0]==']'){
        return -1;
    }
    
    while ( h<100 && pal[h]!=' '){
        if (pal[h]== '.') return 1;
        h++;
    }
    return 0;
}

int main(){
    int tipo,cant,i,*ent,nat,p_imp,profundidad=0;
    float *flo,rea;
    dato d_guardados,*c;
    tLista *a,*b;
    a=init_lista();
    b = a;
    char num[100]; 
    char *p=num;
    ent = &nat;
    flo = &rea;

    printf ("ingrese la cantidad de datos que ingresara: \n");
    scanf( "%d", &cant );

    d_guardados.tipo = 'f'; rea = 4.00 ; d_guardados.contenido = &flo;
    insert(a,-4,d_guardados);
    p_imp = length(a);
    printf ("Largo de la lista: %d\n",p_imp);

    for ( i=0 ; i<cant ; i++ ){
        printf("ingrese la variable: ");
        scanf( "%s", num );
        tipo = identificacion(num);
        if (tipo==ENTERO){
            nat = atoi(p);
            d_guardados.contenido = &ent;
            d_guardados.tipo = 'i';
            append(b,d_guardados);
        }
        else if (tipo==FLOTANTE) {
            rea = atof(p);
            d_guardados.contenido = &flo;
            d_guardados.tipo = 'f';
            append(b,d_guardados);
        }  
        else if (tipo==ABRIRLISTA){
            profundidad++;
            d_guardados.tipo = 'l';
            append(b,d_guardados);
            printf ("%d\n",length(b));
            //c = at(b,(length(b)-1));
            //b = c->contenido;
            i--;

        }
        else{
            profundidad--;
            i--;
            if (profundidad<0){
                i = cant ;//funciona como break
            }
        }  
        
    }
    if (profundidad<0){
        printf("ERROR de sintaxis:\n");
        return 0;
    }

    p_imp = length(a);
    printf ("Largo de la lista: %d\n",p_imp);
    return 0;
}
