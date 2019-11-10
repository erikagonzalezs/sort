/* 
	Archivo: csorth.h
	Erika Gonzalez y Leonel Londono
*/

/*librerias de C*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

/*constantes*/
#define MAXI 1000
#define ruta "./temp/temp"

/*variables globales*/
char*** hilos;
char** archivos;

/*prototipos publicos*/
char** MergeSort(int left, int right,  char** palabras, int cond);
char** Merge(char** palabras, int l, int m, int r);
char** MergeR(char** palabras, int l, int m, int r);
void* OrdenamientoH(void *id);
void* OrdenamientoReversaH(void *id);
void Ordenamiento(char **palabras, int tam, char* nombre);
void OrdenamientoReversa(char **palabras, int tam, char* nombre);
int ContarLineas(char *archivo);
char** LeerArchivo(char* archivo, int tam);
void EscribirArchivo(char** palabras, char nombre[], int tam);
void OrdenarArchivoFinal(char* argv, int argc, int indice);
