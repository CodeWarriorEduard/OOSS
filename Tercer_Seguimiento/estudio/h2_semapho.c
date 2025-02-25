#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sem;

void *routine(void *arg){
    int id = *(int*)arg;
    printf("Hilo %d Esperando el recurso \n", id);
    sem_wait(&sem); // Agarro el recurso
    printf("Hilo %d Accediendo al recurso \n", id);
    sleep(4);
    printf("Hilo %d Liberando \n", id);
    sem_post(&sem);
    free(arg);

}

int main(int argc, char const *argv[])
{
    int nH = 4;
    pthread_t h[nH];
    //Se usará el número de recursos disponibles
    int recursos = 2;

    // Inicializar el semaforo con el número de recursos disponibles

    sem_init(&sem,0,recursos);

    // Crear hilos
    for (int i = 0; i < nH; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&h[i],NULL,&routine, id);
    }
    
    // Join a hilos
    for (int i = 0; i < nH; i++)
    {
        pthread_join(h[i],NULL);
    }

    sem_destroy(&sem);

    return 0;
}
