/*Ejercicio 4
    Define una macro en lenguaje C que tenga la misma funcionalidad que la macro
S_ISREG(mode) usando para ello los flags definidos en <sys/stat.h> para el campo st_mode de
la struct stat, y comprueba que funciona en un programa simple.


Compilar con: gcc -Wall -g -o bin/ej4 src/ej4.c 

*/

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>



#define S_ISREG2(mode)( (mode & S_IFREG) )

/* La macro hace: 

    0100000 (S_IFREG)
AND ??????? (campo st_mode de stat)
    -------

    if( atributos.st_mode & S_IFREG){ // Hacemos AND lógico (bit a bit) si sale 1 es que el bit
                                      // está activo y por tanto es un archivo regular
        printf("Es un archivo regular");
    }else{
        printf("No es un archivo regular");
    }
*/

int main(int argc , char *argv[]){


    struct stat atributos;

    if(argc<2) {
        printf("\nERROR: Por favor, introduzca pathname como argumento\n\n");
        exit(-1);
    }

    printf("%s: ", argv[1]);

    // Llamada a lstat , ahora tengo en atributos los metadatos (estructura stat del archivo)
    
    if(lstat(argv[1],&atributos) < 0) {
            printf("\nError al intentar acceder a los atributos de %s\n",argv[1]);
            perror("\nError en lstat ");
            exit(-1);
    }

    // info del tipo de archivo está en st_mode
    

    if S_ISREG2(atributos.st_mode){
        printf("Es un archivo regular");
    }

    printf("%c",'\n');

	return EXIT_SUCCESS;
}