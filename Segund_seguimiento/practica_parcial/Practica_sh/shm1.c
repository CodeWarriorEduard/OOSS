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
    
    // Crear espacio de memoria compartido.
    int shmid, *c;

    shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|S_IRUSR|S_IWUSR);
   
    c = (int*) shmat(shmid, 0,0);

    if(fork()==0){
        //Hijo.
        FILE *f;
        f = fopen("historia.txt", "r");
        if(f==NULL){       
            perror("Archivo no pudo leerse");
            exit(1);
        }

        char buffer[BUFFER_SIZE];
        char d;
        while((d=getc(f))!=EOF){
            if((d >='a' && d<='z')|| (d >='A' && d<='Z') || d=='\n' || d==' '){
                (*c)++;
            }
        }
        

        shmdt(c);

    }else{
        wait(NULL);
        printf("Hay %d letras en el texto \n", *c);
        shmdt(c);
        shmctl(shmid, IPC_RMID, 0);
    }

    return 0;
}
