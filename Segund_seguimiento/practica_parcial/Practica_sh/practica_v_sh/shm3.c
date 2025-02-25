/*

Crear un vector en memoria compartida que leerá unos enteros de un archivo y repartelo en n procesos.

*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>

int main(int argc, char const *argv[])
{


    FILE *f = fopen(argv[1], "r");

    if(f == NULL){
        perror("Error reading file");
        exit(1);
    }

    int n;
    printf("Ingrese el numero de procesos");
    scanf("%d", &n);

    // Creacion de vector de memoria compartida.

    int tamVector;
    fscanf(f, "%d", &tamVector);

    int idVector, *vectorM = NULL;

    idVector = shmget(IPC_PRIVATE, tamVector*sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);

    // Attach.
    vectorM = (int*) shmat(idVector, 0, 0);

    if(vectorM == NULL){
        perror("Error creando memoria comparida");
        exit(1);
    }

    // // LLenar vector

    for (int idx = 0; idx < tamVector; idx++)
    {
        fscanf(f, "%d", &vectorM[idx]);
    }


    // // Creacion de hijos.
    int i;
    pid_t *childs, padre = getpid();
    // Dividir vector
    int block = tamVector/n;
    int remaining = tamVector % n;
    int start = 0, end;
    
    childs = (pid_t*)malloc(n*sizeof(pid_t));




    for (i = 0; i < n; i++)
    {
        end = start + block + (i<remaining ? 1:0);
        if((childs[i]=fork())==0){
            printf("Process %d %d \n", getpid(), i);
            for (int idx = start; idx < end; idx++)
            {
                printf("[%d] ", vectorM[idx]);
            }
            printf("\n");

            break;
        };
        start = end;
    }

    // Operacion en cada hijo.
    // if(i==n){

    //     wait(NULL);
        
    // }else{
    //     // end = start + block +(i<remaining ? 1:0);
       
    // }


    


    return 0;
}
