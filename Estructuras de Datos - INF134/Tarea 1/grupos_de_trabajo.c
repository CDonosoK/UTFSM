#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
  int id_curso ;
  char sigla_curso [7];
  char nombre_curso [30];
  int integrantes_por_grupo ;
} curso ;

typedef struct {
  char rol_estudiante [12];
  char carrera [4];
  char nombre_completo [41];
  int numero_cursos ;
  int id_cursos_inscritos [50];
} alumno ;

#define MAXALUM 50

//HACER DE NUEVO! EN VEZ DE STRUCT USA LLAMADA CON TODOS LOS DATOS.

void escribir_archivo(int id,char *sigla,char *nomcur,char **alumnos,int tamGrupo,int cantidad_alum){
	if (cantidad_alum > 0){
	    FILE *wp;
	    char *filename = strcat("grupos-",sigla);
	    int booleana[cantidad_alum] = {0};
	    int salir = 1, alumnosGrupo = 0, contadorAlumnos = 0, aux = 0, posicion;
	    char indice_grupo = '1';
	    wp = fopen(strcat(sigla,".txt"),"w");
	    if (wp == NULL){
	      printf("Error en la apertura del archivo.\n");
	      exit(1);
	    }
	    fwrite(sigla, sizeof(char),sizeof(sigla),wp);
	    fwrite(" - ", sizeof(char),3, wp);
	    fwrite(nomcur, sizeof(char), sizeof(nomcur),wp);
	    fwrite("\n\n", sizeof(char),2,wp);
	
	    srand((unsigned)time(NULL));
	    
	    fwrite("Grupo ", sizeof(char),6,wp);
	    fwrite(indice_grupo, sizeof(char), sizeof(indice_grupo), wp);
	    indice_grupo++;
	    fputs(":\n", wp);
	
	    while (salir > 0){
	      if (alumnosGrupo == tamGrupo){
	      	fwrite("\n\n", sizeof(char),2,wp);
	      	fwrite("Grupo ", sizeof(char),6,wp);
	      	fwrite(indice_grupo, sizeof(char), sizeof(indice_grupo), wp);
	      	indice_grupo++;
	      	fputs(":\n", wp);
	      	alumnosGrupo = 0;
		  }
		  while (aux = 0){
		  	//De esta manera nunca se eligirá un alumno que ya se haya elegido.
		  	posicion = rand() % cantidad_alum;
	      	if(!booleana[posicion]){
	        	booleana[posicion] = 1;
	        	aux = 0;
	        }
		  }
	      
	      fwrite(alumnos[posicion],sizeof(char),sizeof(alumnos[posicion]),wp);
	      fputs("\n", wp);
	      contadorAlumnos++;
	      if (contadorAlumnos = cantidad_alum){
	      	salir = 0;
		  }
		}
	    fclose(wp);
	}
}


int main(void){
  int m,n,aux,l,i;
  int count,id,tamGrupo;
  alumno *A;
  curso *C;
  char **alumnos,sigla[7],nomcur[30];
  FILE *fp;

/*
********************************************************************************
Lectura de archivo de alumnos.dat. Objetivo: crear un arreglo de structs para
el futuro uso en generacion de nuevos grupos.
********************************************************************************
*/
  fp = fopen("alumnos.dat","rb");
  if (fp == NULL){
    printf("ERROR! No se pudo abrir el archivo.\n");
    exit(1);
  }

  aux = fread(&n,sizeof(int),1,fp);
  if (aux != 1 ){
    printf("ERROR! No se pudo leer el archivo.\n");
    exit(1);
  }

  A = (alumno *)malloc(sizeof(alumno) * n);
  if (A == NULL){
    printf("ERROR! No se pudo alocar la memoria.\n");
    exit(1);
  }
  aux = fread(A,sizeof(alumno),n,fp);
  fclose(fp);

/*
********************************************************************************
Lectura de archivo de cursos.dat. Objetivo: crear un arreglo de structs para
el futuro uso en generacion de nuevos grupos.
********************************************************************************
*/

  fp = fopen("cursos.dat","rb");
  if (fp == NULL){
    printf("ERROR! No se pudo abrir el archivo.\n");
    exit(1);
  }

  aux = fread(&m,sizeof(int),1,fp);
  if (aux != 1 ){
    printf("ERROR! No se pudo leer el archivo.\n");
    exit(1);
  }

  C = (curso *)malloc(sizeof(curso) * m);
  if (C == NULL){
    printf("ERROR! No se pudo alocar la memoria.\n");
    exit(1);
  }
  aux = fread(C,sizeof(curso),m,fp);
  fclose(fp);

/*
********************************************************************************
Guarda informacion para cada curso en un struct aparte para tener bien
organizado el programa y la informacion que se obtiene del archivo.
********************************************************************************
*/

  for (i = 0; i < m; i++){
    count = 0;
    id = (C+i)->id_curso;
    tamGrupo = (C+i)->integrantes_por_grupo;
    alumnos = (char**)malloc(sizeof(char*)*MAXALUM);
    /*saco primer id de curso*/
    strcpy(sigla,(C+i)->sigla_curso);
    strcpy(nomcur,(C+i)->nombre_curso);
    for (l = 0; l < MAXALUM; l++){
      if (id == (A+i)->id_cursos_inscritos[l]){
        alumnos[l] = (char*)malloc((strlen((A+i)->nombre_completo))*sizeof(char*));
        strcpy(alumnos[l],(A+i)->nombre_completo);
        ++count;
        }
      }
      alumnos = (char**)realloc(alumnos,count*sizeof(char*));

    escribir_archivo(id,sigla,nomcur,alumnos,tamGrupo,count);

    }

  }
