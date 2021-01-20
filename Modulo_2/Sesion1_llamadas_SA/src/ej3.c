/*
Ejercicio 3. ¿Qué hace el siguiente programa?

El programa recibe un argumento(s) (espera pathnames)

Recorre la lista de argumentos y hace lo siguiente:

    * Comprueba si existe el archivo con lstat ( 0 correcto , -1 incorrecto)
    * En el caso de que si exista , identifica de que tipo es con las macros 
    
    * ejemplo de impresión : 
         noticia: Regular
        act_1.txt: Regular
        bin/ej3: Regular
        src/ej2.c: Regular
        ../: Directorio



*/
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
int main(int argc, char *argv[])
{
    int i;
    struct stat atributos;
    char tipoArchivo[30];

    if(argc<2) {
        printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
        exit(-1);
    }

    for(i=1;i<argc;i++) {
        printf("%s: ", argv[i]);
        if(lstat(argv[i],&atributos) < 0) {
            printf("\nError al intentar acceder a los atributos de %s",argv[i]);
            perror("\nError en lstat");
        }else {
            // regular file
			if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
			//directorio
			else if(S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo,"Directorio");
			//etc
			else if(S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo,"Especial de caracteres");
			else if(S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo,"Especial de bloques");
			else if(S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo,"Tuberia con nombre (FIFO)");
			else if(S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo,"Enlace relativo (soft)");
			else if(S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo,"Socket");
			else strcpy(tipoArchivo,"Tipo de archivo desconocido");
			printf("%s\n",tipoArchivo);
        }
    }
    return 0;
}