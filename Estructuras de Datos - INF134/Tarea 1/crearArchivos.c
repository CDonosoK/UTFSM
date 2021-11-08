#include <stdio.h>
#include <stdlib.h>

/*
FUNCIÓN QUE CREA OTROS ARCHIVOS
*/

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

int crearArchivo_cursos(int t_cursos, curso cursos[], int tam, const char *nombreArchivo){
	//ESCRITURA DEL ARCHIVO
	FILE *archivo;
	int i;
	
	archivo = fopen(nombreArchivo, "wb");
	if (archivo == NULL){
		printf("ERROR DE APERTURA");
		return 0;
	}
	//ESCRIBIMOS CUANTOS CURSOS (N STRUCT CURSO)
	fwrite("4",sizeof(int),1,archivo);
	//ESCRIBIMOS TODOS LOS CURSOS
	for (i = 0; i < t_cursos; ++i){
		fwrite(&cursos[i],sizeof(curso),1,archivo);
	}
	fflush(archivo);
	fclose(archivo);
	return 1;
}

int crearArchivo_alumnos(int t_alumno, alumno alumnos[], int tam, const char *nombreArchivo){
	//ESCRITURA DEL ARCHIVO
	FILE *archivo;
	int i;
	
	archivo = fopen(nombreArchivo, "wb");
	if (archivo == NULL){
		printf("ERROR DE APERTURA");
		return 0;
	}
	//ESCRIBIMOS CUANTOS CURSOS (N STRUCT CURSO)
	fwrite("4",sizeof(int),1,archivo);
	//ESCRIBIMOS TODOS LOS CURSOS
	for (i = 0; i < t_alumno; ++i){
		fwrite(&alumnos[i],sizeof(alumno),1,archivo);
	}
	fflush(archivo);
	fclose(archivo);
	return 1;
}
int main()
{
	//VARIABLES DE LOS CURSOS
	int total_cursos = 4;
	
	int id_1,id_2,id_3,id_4;
	id_1 = 1;
	id_2 = 2;
	id_3 = 3;
	id_4 = 4;
	char sigla_1,sigla_2,sigla_3,sigla_4;
	sigla_1 = "INF134";
	sigla_2 = "FIS110";
	sigla_3 = "MAT120";
	sigla_4 = "EFI100";
	char nombre_c_1, nombre_c_2, nombre_c_3, nombre_c_4;
	nombre_c_1 = "Estructura de Datos";
	nombre_c_2 = "Fisica General";
	nombre_c_3 = "Matematicas II";
	nombre_c_4 = "Educacion Fisica";
	int integrantes_1, integrantes_2, integrantes_3, integrantes_4;
	integrantes_1 = 5;
	integrantes_2 = 2;
	integrantes_3 = 10;
	integrantes_4 = 8;
	
	//CREACION DE CURSOS
	curso C1;
	C1.id_curso = id_1;
	C1.sigla_curso = sigla_1;
	C1.nombre_curso = nombre_c_1;
	C1.integrantes_por_grupo = integrantes_1;
	curso C2;
	C2.id_curso = id_2;
	C2.sigla_curso = sigla_2;
	C2.nombre_curso = nombre_c_2;
	C2.integrantes_por_grupo = integrantes_2;
	curso C3;
	C3.id_curso = id_3;
	C3.sigla_curso = sigla_3;
	C3.nombre_curso = nombre_c_3;
	C3.integrantes_por_grupo = integrantes_3;
	curso C4;
	C4.id_curso = id_4;
	C4.sigla_curso = sigla_4;
	C4.nombre_curso = nombre_c_4;
	C4.integrantes_por_grupo = integrantes_4;
	
	curso cursos[] = {C1,C2,C3,C4};
	
	const int tam_c = sizeof(cursos)/sizeof(curso);
	
	//VARIABLES DE ALUMNOS
	int total_alumnos = 4;
	char rol_1, rol_2,rol_3, rol_4;
	rol_1 = "201173546-9";
	rol_2 = "201273546-9";
	rol_3 = "201373546-9";
	rol_4 = "201473546-9";
	char car_1, car_2, car_3, car_4;
	car_1 = "INF";
	car_2 = "MAT";
	car_3 = "QIM";
	car_4 = "ELO";
	char nombre_a_1, nombre_a_2, nombre_a_3,nombre_a_4;
	nombre_a_1 = "JAIMITO";
	nombre_a_2 = "PEDRITO";
	nombre_a_3 = "ANDREA";
	nombre_a_4 = "PALITO";
	int numero_c_1; numero_c_2, numero_c_3, numero_c_4;
	numero_c_1 = 3;
	numero_c_2 = 5;
	numero_c_3 = 1;
	numero_c_4 = 6;
	int id_cursos_insc_1, id_cursos_insc_2, id_cursos_insc_3, id_cursos_insc_4;
	id_cursos_insc_1 = {130, 131, 132};
	id_cursos_insc_2 = {130, 131, 132, 133, 134};
	id_cursos_insc_3 = {130};
	id_cursos_insc_4 = {130, 131, 132,133, 134, 135};
	
	alumno A1;
	A1.rol_estudiante = rol_1;
	A1.carrera = car_1;
	A1.nombre_completo = nombre_a_1;
	A1.numero_cursos = numero_c_1;
	A1.id_cursos_inscritos = id_cursos_insc_1;
	alumno A2;
	A2.rol_estudiante = rol_2;
	A2.carrera = car_2;
	A2.nombre_completo = nombre_a_2;
	A2.numero_cursos = numero_c_2;
	A2.id_cursos_inscritos = id_cursos_insc_2;
	alumno A3;
	A3.rol_estudiante = rol_3;
	A3.carrera = car_3;
	A3.nombre_completo = nombre_a_3;
	A3.numero_cursos = numero_c_3;
	A3.id_cursos_inscritos = id_cursos_insc_3;
	alumno A4;
	A4.rol_estudiante = rol_1;
	A4.carrera = car_4;
	A4.nombre_completo = nombre_a_4;
	A4.numero_cursos = numero_c_4;
	A4.id_cursos_inscritos = id_cursos_insc_4;
	
	
	alumno alumnos[] = {A1,A2,A3,A4};
	
	const int tam_a = sizeof(alumnos)/sizeof(alumno);
	
	crearArchivo(total_cursos, Cursos, tam_c, "Prueba_1_Cursos.dat");
	crearArchivo(total_alumnos, alumnos, tam_a, "Prueba_1_Cursos.dat");
	return 0;
}

