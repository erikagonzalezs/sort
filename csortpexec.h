/* 
	Archivo: csortpexec.h
	Erika Gonzalez y Leonel Londono
*/

/*librerias de C*/
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> 

/*constantes*/
#define MAXI 200
#define ruta "./temp/temp"

/*prototipos publicos*/
void OrdenamientoExecReversa(char *temp, char *input);
void OrdenamientoExec(char *temp, char *input);
