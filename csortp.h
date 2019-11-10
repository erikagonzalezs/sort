/* 
	Archivo: csortp.h
	Erika Gonzalez Leonel Londono
*/

/*librerias de C*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

/*constantes*/
#define MAXI 200
#define ruta "./temp/temp"

/*prototipos publicos*/
char** MergeSort(int left, int right, char **palabras, int cond);
char** Merge(char** palabras, int l, int m, int r);
char** MergeR(char** palabras, int l, int m, int r);
void Ordenamiento(char *archivo, int tam, int i);
void OrdenamientoReversa(char *archivo, int tam, int argc);
int ContarLineas(char *archivo);
char** LeerArchivo(char* archivo, int tam);
void EscribirArchivo(char** palabras, char nombre[], int tam);
void EscribirArchivoFinal(char* argv, int argc, int indice);
