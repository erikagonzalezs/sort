/* 
	Archivo: csortp.c
	Erika Gonzalez y Leonel Londono
*/

#include "csortp.h"

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
		
		if(cond == 0){
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

void Ordenamiento(char *archivo, int tam, int argc)
{
	char aux[MAXI];
	int i = 0, j = 0, k = 0;
	char nombre[MAXI];
	char** palabras = LeerArchivo(archivo, tam);

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
	
	sprintf(nombre, "%s%d.txt", ruta, argc);
	EscribirArchivo(palabras, nombre, tam);	
}

void OrdenamientoReversa(char *archivo, int tam, int argc)
{
	char aux[MAXI];
	int i = 0, j = 0, k = 0;
	char nombre[MAXI];
	char** palabras = LeerArchivo(archivo, tam);

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

	sprintf(nombre, "%s%d.txt", ruta, argc);
	EscribirArchivo(palabras, nombre, tam);	
}

void EscribirArchivo(char** palabras, char nombre[], int tam) 
{
	FILE *fich;
	int i = 0;

	fich = fopen(nombre, "w");

	if(fich != NULL){
		for(i = 0; i<tam; ++i){
        		fputs(palabras[i], fich);
    		}	
    		fclose(fich);
	}else{
		perror("No se pudo crear el archivo");
	}
}

void EscribirArchivoFinal(char* argv, int argc, int indice)
{
	int cont = 0;
	int i = 0;
	char nombre[MAXI];
	char linea[MAXI];
	FILE *final;
	FILE *temp;

	final = fopen(argv, "a");
	if(final != NULL){
		for(i = indice; i < argc-1; i++){
			
			sprintf(nombre, "%s%d.txt", ruta, ++cont);
			temp = fopen(nombre, "r");
			if(temp != NULL){
				while(fgets(linea, MAXI, (FILE*) temp)) {
					fputs(linea, final);
				}
				fclose(temp);
			}else{
				perror("No se pudo abrir el archivo");
				exit(1);
			}
		}
		fclose(final);
	}else{
		perror("No se pudo crear el archivo final");
		exit(1);
	}
	
	
}

int main (int argc, char *argv[]) 
{
	int status;
	int i = 0;
	int tam = 0;
	char **final;
	char **palabras;
	pid_t hijos;

	if(strcmp(argv[1], "-r") == 0)
	{
		if(argc > 12)
		{
			perror("Cantidad de archivos mayor a la permitida");
			exit(0);
		}
		else
		{
			for(i = 2; i < argc-1; i++)
			{
				
				if((hijos = fork()) < 0 )
				{
					perror("Error en el fork");
					exit(0);
				}
				if(hijos == 0)
				{
					tam = ContarLineas(argv[i]);
					if (tam == 0)
					{
						perror("Archivo vacio");
						exit(0);
					}
					OrdenamientoReversa(argv[i], tam, i-1);
					exit(0);
				}
			}
			while((hijos = wait(&status)) != -1);	
			EscribirArchivoFinal(argv[argc-1], argc, 2);
			tam = ContarLineas(argv[argc-1]);
			palabras = LeerArchivo(argc[argv-1],tam);
			final = MergeSort(0, tam-1, palabras, 1);
			EscribirArchivo(final,argv[argc-1],tam);	
		}
	}
	else
	{
		if(argc > 11)
		{
			perror("Cantidad de archivos mayor a la permitida");
			exit(0);
		}
		else
		{
			for(i = 1; i < argc-1; i++)
			{
				if((hijos = fork()) < 0 )
				{
					perror("Error en el fork");
					exit(0);
				}
				if(hijos == 0)
				{
					tam = ContarLineas(argv[i]);
					if (tam == 0)
					{
						perror("Archivo vacio");
						exit(0);
					}
					Ordenamiento(argv[i], tam, i);
					exit(0);
				}
			}
			while((hijos = wait(&status)) != -1);
			EscribirArchivoFinal(argv[argc-1], argc, 1);
			tam = ContarLineas(argv[argc-1]);
			palabras = LeerArchivo(argc[argv-1],tam);
			final = MergeSort(0, tam-1, palabras, 0);
			EscribirArchivo(final,argv[argc-1],tam);
		} 	
	}
	return 0;
}


