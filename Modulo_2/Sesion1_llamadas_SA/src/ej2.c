/*
tarea2.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''


Acepta como argumento pathname lo abre y lo lee en bloques de 80B

Devuelve un archivo salida.txt con el formato: 
	
	Bloque 1
	// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
	Bloque 2
	// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
	...



COMPILAR CON : gcc -Wall -g -o bin/ej2 src/ej2.c 

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
#include<string.h>



const int num_bytes = 80 , 
	      tam_block_msg = 12;


int main(int argc, char *argv[])
{
	int i;

	struct stat atributos;
	char tipoArchivo[30];
	
	int fd_origen , 
		fd_destino; //descriptor del archivo

	
	char buffer[num_bytes]; // buffer donde se guardan los bytes leidos
	


	// Si no se ha pasado un argumento , devuelve mensaje de error y sale
	if(argc<2) {
		printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
		exit(EXIT_FAILURE);
	}



	for(i=1;i<argc;i++) {
		printf("%s: ", argv[i]);
		// Consulta info del archivo , si este no existe , lstat devuelve -1
		// lstat devuelve la info del archivo en el buffer atributos
		if(lstat(argv[i],&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de %s \n",argv[i]);
			perror("\nError en lstat ");
		}
		// si es correcto , identifica archivo 
		// atributos.st_mode contiene info del tipo de archivo
		else {
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

	// Abrimos archivo
	// O_RDONLY : read only
	// S_IRUSR :  00400 user has read permission


	}

	// Abrimos el archivo que queremos leer
	if( (fd_origen = open(argv[1] , O_RDONLY)) < 0 ){
		printf("\nError %d en open  :",errno);
		perror("\nError en open");
	}

	// Abrimos / Creamos el archivo donde escribimos
	if ( (fd_destino = open("resultados/res_ej2.txt",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR)) < 0 ){
		printf("\nError %d en open  :",errno);
		perror("\nError en open");
	}

	// le metemos caracteres nulos para luego escribir el 
	// mensaje de nº de bloques (parte 2 de la actividad).
	// Como buffer está vacio al inicio , le metemos esos caracteres nulos
	write(fd_destino , &buffer , 36);


	//leemos el archivo origen en tramos de 80 B
	// mientras el numero de bytes leidos sea mayor que 0
	int bytes_leidos , 
		num_bloque = 1;

	while ( (bytes_leidos=read(fd_origen,&buffer,num_bytes)) > 0){

		char mensaje_bloque[10]; //reservamos espacio mensaje del numero de bloque
		sprintf(mensaje_bloque,"Bloque %i\n",num_bloque); 

		//Escribimos el mensaje del nº de bloque
		write(fd_destino,&mensaje_bloque,10);
		//Escrimos los 80 Bytes ( o los que se hayan podido leer)
		write(fd_destino,&buffer,bytes_leidos);
		//Salto de linea
		write(fd_destino,"\n",1);

		num_bloque++;
	}

	// Nos vamos al inicio del archivo y metemos el mensaje del numero de bloques
	if ( lseek(fd_destino , 0 , SEEK_SET) < 0 ){ // offset a 0
		perror("\nError en lseek");
		exit(EXIT_FAILURE);
	} 
	
	char msj_final[36]; //reserva de espacio
	sprintf(msj_final , "El número total de bloques es %i\n",num_bloque-1); 
	write(fd_destino,msj_final,sizeof(msj_final));


	// CERRAMOS LOS DOS ARCHIVOS

	close(fd_origen);
	close(fd_destino);

	
	return EXIT_SUCCESS;


}
