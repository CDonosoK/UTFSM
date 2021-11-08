#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---------- MODIFICAR ESTO ----------

#define OUTP "productos.dat"  // Nombre del archivo de productos
#define REFP "productos_reference.txt"  // Nombre de la referencia de productos
#define OUTO "ofertas.dat"  // Nombre del archivo de ofertas
#define REFO "ofertas_reference.txt"  // Nombre de la referencia de ofertas
#define PRUEBA "compras.txt"

int numP = 60;  // Cantidad de productos
int p = 61;
int codP[] = {1, 2, 3, 4, 5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60};  // Codigos de los productos
char *nbreP[] = {"Manzana","Guantes","Steak","Donut","Carbon","Nuggets","Zanahoria","Lomito","Tomate","Pepino","Grua","Agua","Papas Fritas","Salchichas","Pepsi","Coca Cola", "Pera", "Jabon", "Bebida","Tula","Frac","Anticucho","Clorox","Pan integral", "Pan","Atun","Carne","Huevo","Sardinas","Leche","Bacalao","Ostras","Chocolate","Trencito","Monster","Score","Te","Vino","Cerveza","Carne","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","x","z"};
int precioP[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60};  // Precios de los productos

int numO = 5;  // Cantidad de ofertas
int codO[] = {4, 5, 6, 2, 15};  // Codigos de los productos en oferta
int cantidadO[] = {3, 6, 2, 2,3};  // Cantidad de productos por oferta
int descuentoO[] = {800, 160, 200, 100, 200};  // Descuentos

// ---------- MODIFICAR ESTO ----------

typedef struct {
	int cod_producto;
	char nbre_producto[31];
	int precio;
} producto;

typedef struct {
	int cod_producto;
	int cantidad_descuento;
	int descuento;
} oferta;

producto P;
oferta O;

int main() {
	FILE *outP = fopen(OUTP, "w");
	if (outP == NULL) { printf("Error al abrir %s\n", OUTP); exit(-1); }
	FILE *refP = fopen(REFP, "w");
	if (refP == NULL) { printf("Error al abrir %s\n", REFP); exit(-1); }
	FILE *outO = fopen(OUTO, "w");
	if (outO == NULL) { printf("Error al abrir %s\n", OUTO); exit(-1); }
	FILE *refO = fopen(REFO, "w");
	if (refO == NULL) { printf("Error al abrir %s\n", REFO); exit(-1); }
	FILE *prueba = fopen(PRUEBA, "w");
	if (prueba == NULL) { printf("Error al abrir %s\n", PRUEBA); exit(-1); }

	fwrite(&numP, sizeof(int), 1, outP);
	fprintf(refP, "Cantidad de structs: %d\n", numP);
	for (int i = 0; i < numP; i++) {
		P.cod_producto = codP[i];
		strcpy(P.nbre_producto, nbreP[i]);
		P.precio = precioP[i];
		fwrite(&P, sizeof(producto), 1, outP);
		fprintf(refP, "\n[Struct %d]\n", i + 1);
		fprintf(refP, "  cod_producto: %d\n  nbre_producto: %s\n  precio: %d\n", P.cod_producto, P.nbre_producto, P.precio);
	}

	fwrite(&numO, sizeof(int), 1, outO);
	fprintf(refO, "Cantidad de structs: %d\n", numO);
	for (int i = 0; i < numO; i++) {
		O.cod_producto = codO[i];
		O.cantidad_descuento = cantidadO[i];
		O.descuento = descuentoO[i];
		fwrite(&O, sizeof(oferta), 1, outO);
		fprintf(refO, "\n[Struct %d]\n", i + 1);
		fprintf(refO, "  cod_producto: %d\n  cantidad_descuento: %d\n  descuento: %d\n", O.cod_producto, O.cantidad_descuento, O.descuento);
	}
	int a  = 61;
	fprintf(prueba,"%d\n",a);
	for(int i = 1; i < 61; i++){
		fprintf(prueba,"%d\n",i);
		for(int n = 0; n<i; n++){
			fprintf(prueba, "%d\n", i);
		}	
	}
	fprintf(prueba,"%d\n",119);
	for(int i = 1; i < 61; i++){
		fprintf(prueba,"%d\n",i);
	}
	for(int i = 59; i > 0; i--){
		fprintf(prueba,"%d\n",i);
	}

	fclose(outP);
	fclose(refP);
	fclose(outO);
	fclose(refO);
	fclose(prueba);

	return 0;
}
