/* 
	Archivo: csortpexec.h
	Erika Gonzalez y Leonel Londono
*/

#include "csortpexec.h"

void OrdenamientoExecReversa(char *temp, char *input)
{
	int fich;
	char *comando[MAXI];
	
	comando[0] ="sort";
	comando[1] = input; 
	comando[2] = "-r";
	comando[3] = NULL;
	/* trozo de codigo sacado de: https://stackoverflow.com/questions/33323449/how-to-use-execvp-in-c-to-sort-a-file-and-write-into-another-file*/
	fich = open(temp, O_WRONLY | O_CREAT, 0777 );
    	if( fich == -1 ) 
	{
       	perror("No se pudo abrir el archivo");
       	exit(1);
   	}
    	fclose(stdout);
    	dup2(fich, STDOUT_FILENO);
    	close(fich);
    	execvp(comando[0],comando);
}
void OrdenamientoExec(char *temp, char *input)
{
	int fich;
	char *comando[MAXI];
	
	comando[0] ="sort";
	comando[1] = input; 
	comando[2] = NULL;
	/* trozo de codigo sacado de: https://stackoverflow.com/questions/33323449/how-to-use-execvp-in-c-to-sort-a-file-and-write-into-another-file*/
	fich = open(temp, O_WRONLY | O_CREAT, 0777 );
    	if( fich == -1 ) 
	{
       	perror("No se pudo abrir el archivo");
       	exit(1);
   	}
    	fclose(stdout);
    	dup2(fich, STDOUT_FILENO);
    	close(fich);
    	execvp(comando[0],comando);
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
	pid_t hijos;
   	char *input;
	char *output = argv[argc-1];
	char temp[MAXI];

	if(strcmp(argv[1], "-r") == 0)
	{
		if(argc > 12)
		{
			perror("Cantidad de archivos mayor a la permitida");
			exit(1);
		}
		else
		{
			for(i = 2; i < argc-1; i++)
			{
				if((hijos = fork()) < 0 )
				{
					perror("Error en el fork");
					exit(1);
				}
				if(hijos == 0)
				{
					input = argv[i];
					sprintf(temp, "%s%d.txt", ruta, i-1);
					OrdenamientoExecReversa(temp, input);
				}
			}
			while((hijos = wait(&status)) != -1);	
			EscribirArchivoFinal(argv[argc-1], argc, 2);
			OrdenamientoExecReversa(output, output);	
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
					input = argv[i];
					sprintf(temp, "%s%d.txt", ruta, i);
					OrdenamientoExec(temp, input);
				}
			}
			while((hijos = wait(&status)) != -1);
			EscribirArchivoFinal(argv[argc-1], argc, 1);
			OrdenamientoExec(output, output);
		} 	
	}

	return 0;
}

