/*
tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probar tras la ejecuci�n del programa: $>cat archivo y $> od -c archivo
*/


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ\n"; 

int main(int argc, char *argv[])
{
int fd; //file descriptor del archivo

/* O_CREAT : If pathname does not exist, create it as a regular file.
   O_TRUNC : Si el archivo existe y permite escritura , lo trunca a longitud 0
   O_WRONLY : Abrir solo para escritura
   S_IRUSR : 00 400 (user permisos de  lectura )
   S_IWUSR   00 200 (user tiene permisos de escritura )

   En este caso , el user tiene permisos de escritura y lectura sobre el nuevo archivo
   (si se crea al llamar a open)
*/


// ABRIMOS / CREAMOS ARCHIVO
if( (fd=open("resultados/act1.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	
	// si open devuelve error , se imprime el error 

	printf("\nError %d en open",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

// si se ha llegado aqui , el fd esta asociado al archivo abierto por open

// ESCRIBIMOS EN EL ARCHIVO
if(write(fd,buf1,10) != 10) {

	// si write da error ( que ocurre cuando count != numero devuelto)
	// se imprime error por salida error estandar

	perror("\nError en primer write");
	exit(EXIT_FAILURE);
}

// si se ha llegado aqui , se han escrito abcdefghij en el archivo asociado con fd

// MOVEMOS EL OFFSET 40 Bytes desde el inicio 
// ya que cada char vale 4B , como tenemos 10 chars , hay que desplazarse 40 B

if(lseek(fd,40,SEEK_SET) < 0) {
	perror("\nError en lseek");
	exit(EXIT_FAILURE);
}

//ESCRIBIMOS EN BUFFER 2
if(write(fd,buf2,11) != 11) {
	perror("\nError en segundo write");
	exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;
}
