/* 
	Archivo: csorth.c
	Erika Gonzalez y Leonel Londono
*/

#include "csorth.h"

char** Merge(char** palabras, int l, int m, int r) 
{ 
	/*TROZO DE CODIGO SACADO DE https://www.geeksforgeeks.org/merge-sort/*/
	int i, j, k; 
    	int n1 = m - l + 1; 
    	int n2 =  r - m; 
  
    	char **left;
	char **right; 

	left = malloc(sizeof(char*) * n1);
	for(i = 0; i < n1; i++){
		left[i] = malloc(sizeof(char) * MAXI);
	}

	right = malloc(sizeof(char*) * n2);
	for(i = 0; i < n2; i++){
		right[i] = malloc(sizeof(char) * MAXI);
	}


    	for (i = 0; i < n1; i++){
       		strcpy(left[i],palabras[l + i]); 
	}
    	for (j = 0; j < n2; j++){ 
       		strcpy(right[j],palabras[m + 1+ j]); 
	}
  
    	i = 0; 
    	j = 0; 
    	k = l; 
    	while (i < n1 && j < n2) { 
        	if (strcmp(left[i],right[j]) < 0 ) { 
            		strcpy(palabras[k],left[i]); 
            		i++; 
       	}else{ 
            		strcpy(palabras[k],right[j]); 
            		j++; 
        	}  
		k++;
    	} 
    	while (i < n1) { 
        	strcpy(palabras[k],left[i]);
        	i++; 
        	k++; 
    	} 

    	while (j < n2) { 
        	strcpy(palabras[k],right[j]);  
        	j++; 
        	k++; 
    	} 
	return palabras;
} 

char** MergeR(char** palabras, int l, int m, int r) 
{ 
	/*TROZO DE CODIGO SACADO DE https://www.geeksforgeeks.org/merge-sort/*/
	int i, j, k; 
    	int n1 = m - l + 1; 
    	int n2 =  r - m; 
  
   	char **left;
	char **right; 

	left = malloc(sizeof(char*) * n1);
	for(i = 0; i < n1; i++){
		left[i] = malloc(sizeof(char) * MAXI);
	}

	right = malloc(sizeof(char*) * n2);
	for(i = 0; i < n2; i++){
		right[i] = malloc(sizeof(char) * MAXI);
	}

    	for (i = 0; i < n1; i++){
       		strcpy(left[i],palabras[l + i]); 
	}
    	for (j = 0; j < n2; j++){ 
       		strcpy(right[j],palabras[m + 1+ j]); 
	}
  
    	i = 0; 
    	j = 0; 
    	k = l; 
    	while (i < n1 && j < n2) { 
        	if (strcmp(left[i],right[j]) > 0 ) { 
            		strcpy(palabras[k],left[i]); 
            		i++; 
       	}else{ 
            		strcpy(palabras[k],right[j]); 
            		j++; 
        	}  
		k++;
    	} 

    	while (i < n1) { 
        	strcpy(palabras[k],left[i]);
        	i++; 
        	k++; 
    	} 

    	while (j < n2) { 
        	strcpy(palabras[k],right[j]);  
        	j++; 
        	k++; 
    	} 
	return palabras;
} 

char** MergeSort(int left, int right,  char** palabras, int cond)
{ 
	/*TROZO DE CODIGO SACADO DE https://www.geeksforgeeks.org/merge-sort/*/
	int m = 0;
    	if (left < right) { 
		m = left+(right-left)/2; 
       	palabras = MergeSort(left, m, palabras, cond); 
        	palabras = MergeSort(m+1, right, palabras, cond); 
		
		if(cond == 1){
       		palabras = Merge(palabras, left, m, right);
		}else{
			palabras = MergeR(palabras, left, m, right);
		}
	}
	return palabras;
}

int ContarLineas(char* archivo)
{
	FILE *fich;
	int tam = 0;
	fich = fopen(archivo, "r");
	char linea[MAXI];

	if(fich != NULL){
		while(fgets(linea, MAXI, (FILE*) fich)){
			tam++;
    		}
	fclose(fich);
	}else{
		perror("No se pudo abrir el archivo");
		exit(1);
	}
	return tam;
}

char** LeerArchivo(char* archivo, int tam)
{
	FILE *fich;
	char linea[MAXI];
	int cont = 0;
	int i = 0;
	char** palabras;

	fich = fopen(archivo, "r");
	palabras = malloc(sizeof(char*) * tam);
	for(i = 0; i < tam; i++){
		palabras[i] = malloc(sizeof(char) * MAXI);
	}

	if(fich != NULL){
		while(fgets(linea, MAXI, (FILE*) fich)){
			strcpy(palabras[cont], linea);
			cont++;
    		}	
    		fclose(fich);
	}else{
		perror("No se pudo abrir el archivo");
		exit(1);
	}
	return palabras;

}

void* OrdenamientoH(void *id)
{
	int code = *(int*) id;
	char aux[MAXI];
	int i = 0, j = 0, k = 0;
	int tam = ContarLineas(archivos[code]);

	char** palabras = LeerArchivo(archivos[code], tam);

	for(i = 0; i<tam-1; i++){
        	k=i;
        	strcpy(aux, palabras[i]);
        	for(j = i+1; j<tam; j++){
            		if(strcmp(palabras[j], aux)<0){
                		k=j;
                		strcpy(aux, palabras[j]);
            		}
        	}
        	strcpy(palabras[k],palabras[i]);
        	strcpy(palabras[i],aux);
    	}

	hilos[code] = palabras;	
	pthread_exit(NULL);	
}

void* OrdenamientoReversaH(void *id)
{
	int code = *(int*) id;
	char aux[MAXI];
	int i = 0, j = 0, k = 0;
	int tam = ContarLineas(archivos[code]);
	char** palabras = LeerArchivo(archivos[code], tam);

	for(i = 0; i<tam-1; i++){
        	k=i;
        	strcpy(aux, palabras[i]);
        	for(j = i+1; j<tam; j++){
            		if(strcmp(palabras[j], aux) > 0){
                		k=j;
                		strcpy(aux, palabras[j]);
            		}
        	}
        	strcpy(palabras[k],palabras[i]);
        	strcpy(palabras[i],aux);
    	}

	hilos[code] = palabras;	
	pthread_exit(NULL);
}

void Ordenamiento(char **palabras, int tam, char *nombre)
{
	char aux[MAXI];
	int i = 0, j = 0, k = 0;

	for(i = 0; i<tam-1; i++){
        	k=i;
        	strcpy(aux, palabras[i]);
        	for(j = i+1; j<tam; j++){
            		if(strcmp(palabras[j], aux)<0){
                		k=j;
                		strcpy(aux, palabras[j]);
            		}
        	}
        	strcpy(palabras[k],palabras[i]);
        	strcpy(palabras[i],aux);
    	}	
	EscribirArchivo(palabras, nombre, tam);
}

void OrdenamientoReversa(char **palabras, int tam, char* nombre)
{
	char aux[MAXI];
	int i = 0, j = 0, k = 0;

	for(i = 0; i<tam-1; i++){
        	k=i;
        	strcpy(aux, palabras[i]);
        	for(j = i+1; j<tam; j++){
            		if(strcmp(palabras[j], aux) > 0){
                		k=j;
                		strcpy(aux, palabras[j]);
            		}
        	}
        	strcpy(palabras[k],palabras[i]);
        	strcpy(palabras[i],aux);
    	}
	EscribirArchivo(palabras, nombre, tam);	
}

void EscribirArchivo(char** palabras, char nombre[], int tam) 
{
	FILE *fich;
	int i = 0;

	fich = fopen(nombre, "a");

	if(fich != NULL){
		for(i = 0; i<tam; ++i){
        		fputs(palabras[i], fich);
    		}	
    		fclose(fich);
	}else{
		perror("No se pudo crear el archivo");
	}
}

void OrdenarArchivoFinal(char* argv, int numHilos, int cond)
{
	int cont = 0;
	int i = 0, j = 0;
	int totaLineas = 0;
	int contar[numHilos];
	char **palabras;
	char **salida;

	for(i = 0;  i < numHilos; i++){
		contar[i] = ContarLineas(archivos[i]);
		totaLineas += contar[i]; 
	}
	
	palabras = malloc(sizeof(char*) * totaLineas );
	for(i = 0; i < totaLineas; i++){
		palabras[i] = malloc(sizeof(char) * MAXI);
	}

	for(i = 0; i < numHilos; i++){
		for(j = 0; j < contar[i]; j++){
			strcpy(palabras[cont++], hilos[i][j]); /*copio de la matriz al array*/
		}
	}
	
	if(cond == 1){
		
		salida = MergeSort(0, totaLineas-1, palabras, 1);
		
	}else{
		
		salida = MergeSort(0, totaLineas-1, palabras, 0);
	}
	EscribirArchivo(salida, argv, totaLineas);
}

int main (int argc, char *argv[]) 
{
	int i = 0;
	int numHilos;
	int *ids;
	pthread_t *hilosArray;

	if(strcmp(argv[1], "-r") == 0){
		archivos = argv+2;
		numHilos = argc-3;
		hilos = malloc(sizeof(char**) * numHilos);
		hilosArray = malloc(sizeof(pthread_t) * numHilos);
		ids = malloc(sizeof(int) * numHilos);
		if(argc > 12){
			perror("Cantidad de archivos mayor a la permitida");
			exit(0);
		}
		else{
			for(i = 0; i < numHilos; i++){
				ids[i] = i;
				pthread_create(&hilosArray[i], NULL, (void* )OrdenamientoReversaH, (void*) &ids[i]);
			}
		}
	}
	else{
		archivos = argv+1;
		numHilos = argc-2;
		hilos = malloc(sizeof(char**) * numHilos);
		hilosArray = malloc(sizeof(pthread_t) * numHilos);
		ids = malloc(sizeof(int) * numHilos);
		if(argc > 11){
			perror("Cantidad de archivos mayor a la permitida");
			exit(0);
		}
		else{
			for(i = 0; i < numHilos; i++){
				ids[i] = i;
				pthread_create(&hilosArray[i], NULL, (void* )OrdenamientoH, (void*) &ids[i]);
			}
		}
	}
	for(i = 0; i < numHilos; i++ ){
		pthread_join (hilosArray[i], NULL);
	}

	if(strcmp(argv[1], "-r") == 0){
		OrdenarArchivoFinal(argv[argc-1], numHilos, 0);
	}
	else{
		OrdenarArchivoFinal(argv[argc-1], numHilos, 1);
	}
	return 0;
}












