#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include <bits/pthreadtypes.h>


pthread_barrier_t barrier;

void *routine(void *arg){
    int id = *(int *)arg;
    printf("Hilo %d realizando primera tarea \n", id);
    pthread_barrier_wait(&barrier);
    
    printf("Hilo %d realizando segunda tarea \n", id);
    
}

int main(int argc, char const *argv[])
{

    int nH = atoi(argv[1]);

    if(nH < 0){
        perror("Error numero de hilos debe ser mayor a cero");
        exit(1);
    }
    // Crear vector de hilos
    pthread_t *h;
    h = (pthread_t*)malloc(nH*sizeof(pthread_t));



    // Inicializar
    pthread_barrier_init(&barrier, NULL, nH);


    // Creear hilos

    for (int i = 0; i < nH; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&h[i],NULL,routine,id);
    }
    
    //Join

    for (int i = 0; i < nH; i++)
    {
        pthread_join(h[i], NULL);
    }
    


    pthread_barrier_destroy(&barrier);
    return 0;
}
