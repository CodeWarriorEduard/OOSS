/*

Crear un programa que mediante dos procesos (padre e hijo) el hijo leerá el archivo y contará las cantidades de letras que hay en el texto
el contador usará memoria compartida y el padre accederá a este contador e imprimirá la cantidad de letras contadas.

*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#define BUFFER_SIZE 1024    

int main(int argc, char const *argv[])
{
    
    return 0;
}
