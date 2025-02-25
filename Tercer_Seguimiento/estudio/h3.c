#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


// Crear semaforo
sem_t sem;
int c = 0;

void *routine(void *arg){
    int id = *(int *) arg;
    sem_wait(&sem);
    printf("Incrementando hilo %d \n", id);
    c++;
    printf("Valor de c actual %d \n", c);
    sem_post(&sem);
    free(arg);
    printf("\n");
}

int main(int argc, char const *argv[])
{
    pthread_t h[10]; //Crear 10 hilos que accedan solo 3 al contador y lo incrementen.
    int q = 3;
    sem_init(&sem,0,q);

    
    for (int i = 0; i < 10; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&h[i],NULL,&routine, id);
    }

    // Join

     for (int i = 0; i < 10; i++)
    {
        pthread_join(h[i],NULL);
    }

    printf("Contador %d \n", c);
    sem_destroy(&sem);
    


    return 0;
}
