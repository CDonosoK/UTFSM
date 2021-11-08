#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************
			STRUCT Y FUNCIONES
*************************************/

typedef struct{
	int id_curso;
	char sigla_curso[7];
	char nombre_curso[30];
	int integrantes_por_grupo;
} curso;

typedef struct{
	char rol_estudiante[12];
	char carrera[4];
	char nombre_completo[41];
	int numero_cursos;
	int id_cursos_inscritos[50];
} alumno;

typedef struct{
	char nombre_completo[41];
	/************************************
	UN ALUMNO TENDRÁ UN MÁXIMO DE 10 CURSOS(?)
	*************************************/
	int grupo_cursos[10]; 
} aux_alumno;

aux_alumno leerAlumnos(){
	int aux_1,n,numero_alumno, numero_cursos_alumno_nuevo, curso_alumno;
	alumno *A;
	FILE *archivo;
	
	/************************************
			LECTURA DEL ARCHIVO
					Y
			MANEJO DE ERRORES
	*************************************/
	archivo = fopen("alumnos.dat","rb");
	if (archivo == NULL){
		puts("Error de apertura del archivo \n");
	}
	aux_1 = fread(&n,sizeof(int),1,archivo);
	if (aux_1 != 1){
		puts("Error de lectura del archivo \n");
	}
	A = (alumno *)malloc(n*sizeof(alumno));
	if (A == NULL){
		puts("Error de memoria del archivo \n");
	}
	aux_1 = fread(A,sizeof(alumno),n,archivo);
	fclose(archivo);
	
	/************************************
			CREO EL ARRAY CON EL LARGO
			DE LA CANTIDAD DE ALUMNOS
	*************************************/
	aux_alumno cantidad_alumnos[n], *P_cantidad_alumnos;	
	
	numero_alumno = 0;
	for (numero_alumno ; numero_alumno< n; numero_alumno++)
	{
		/************************************
			CREO AL ALUMNO A PARTIR DEL STRUCT AUX_ALUMNO
	*************************************/
	  aux_alumno alumno_nuevo;
	  strcpy(alumno_nuevo.nombre_completo, (A+numero_alumno)->nombre_completo);
	  numero_cursos_alumno_nuevo = (A+numero_alumno)->numero_cursos;
	  
	  /************************************
			GUARDO LOS ID DE LOS CURSOS DE CADA ALUMNO
	*************************************/
	  for (curso_alumno = 0; curso_alumno < numero_cursos_alumno_nuevo; curso_alumno++){
	  	int id_curso_alumno;
	  	char id_curso_alumno_c;
	  	id_curso_alumno = (A+numero_alumno)->id_cursos_inscritos[curso_alumno];
	  	//printf("ID CURSOS: %i\n",id_curso_alumno);
	  	alumno_nuevo.grupo_cursos[curso_alumno] = id_curso_alumno;
	  }
	  /************************************
			UNA VEZ OBTENIDO EL NOMBRE DEL ALUMNO Y
			LOS CURSOS QUE ESTÁ TENIENDO. LOS GUARDAMOS EN EL ARRAY
			CANTIDAD DE ALUMNOS
	*************************************/
	  cantidad_alumnos[numero_alumno] = alumno_nuevo;
	}	
	/************************************
			UNA VEZ OBTENIDO TODOS LOS ALUMNOS Y GUARDADOS EN EL ARRAY
			RETORNO ESTE ARRAY PARA SER UTILIZADO MÁS ADELANTE.
			CADA ALUMNO NUEVO RECORDAMOS QUE ESTÁ COMPUESTO POR:
			- NOMBRE
			- ID DE CURSOS QUE INSCRIBIÓ
	*************************************/
	//return cantidad_alumnos;
}

void leerCursos(){

	int aux_1,cantidad_de_cursos,curso_nuevo;
	curso *C;
	FILE *archivo;
	
	/************************************
			LECTURA DEL ARCHIVO
					Y
			MANEJO DE ERRORES
	*************************************/
	archivo = fopen("cursos.dat","rb");
	if (archivo == NULL){
		puts("Error de apertura del archivo \n");
	}
	aux_1 = fread(&cantidad_de_cursos,sizeof(int),1,archivo);
	if (aux_1 != 1){
		puts("Error de lectura del archivo \n");
	}
	C = (curso *)malloc(cantidad_de_cursos*sizeof(curso));
	if (C == NULL){
		puts("Error de memoria del archivo \n");
	}
	aux_1 = fread(C,sizeof(curso),cantidad_de_cursos,archivo);
	fclose(archivo);
	curso_nuevo = 0;
	for (curso_nuevo ; curso_nuevo < cantidad_de_cursos; curso_nuevo ++)
	{
	  /***************************************
	  LLAMO A LA FUNCION PARA CREAR EL ARCHIVO DE CADA CURSO
	  ****************************************/
	  escribirArchivo((C+curso_nuevo)->sigla_curso,(C+curso_nuevo)->nombre_curso, 2);
	}	
}

void escribirArchivo( char sigla_curso[7], char nombre_curso[30], int integrantes){
	FILE *archivo;
	/***************************************
	  INICIALIZAMOS VARIABLES A OCUPAR
	  ****************************************/
	char sigla_archivo[11];
	strcpy(sigla_archivo,sigla_curso);
	strcat(sigla_archivo,".txt");
	int numero_grupo;
	char numero_grupo_c[3];
	/***************************************
	  CREO EL ARCHIVO CON EL NOMBRE DEL CURSO
	  ****************************************/
	archivo = fopen(sigla_archivo,"w");
	if (archivo == NULL){
		puts("Error de apertura del archivo \n");
	}
	/***************************************
	  COLOCAMOS EL ENCABEZADO DE CADA ARCHIVO DE TEXTO
	  SIGLA DEL CURSO - NOMBRE DEL CURSO
	  ****************************************/
	fputs(sigla_curso,archivo);
	fputs(" - ", archivo);
	fputs(nombre_curso, archivo);
	fputs("\n\n", archivo);
	//TENGO QUE ARREGLAR ESTE FOR
	for (numero_grupo = 1; numero_grupo <= integrantes; numero_grupo++){
		/***************************************
			  COLOCAMOS EL ENCABEZADO DE 
			  		CADA GRUPO
	  ****************************************/
		fputs("Grupo ",archivo);
		sprintf(numero_grupo_c,"%d", numero_grupo);
		fputs(numero_grupo_c, archivo);
		fputs(":\n",archivo);
		/***************************************
			  COLOCAMOS LOS INTEGRANTES DE CADA GRUPO
	  ****************************************/
	  fputs("\n",archivo);
	}
}

int main(){
	leerAlumnos();
	return 0;
}

