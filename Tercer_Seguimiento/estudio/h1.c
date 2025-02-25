#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

// Contador
int c = 0;
int q = 0;
// Mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *routineCounter(){

    for (int i = 0; i < q; i++)
    {
        //Lock
        pthread_mutex_lock(&mutex);
        c++;
        pthread_mutex_unlock(&mutex);
        //Unlock
    }
    
}

int main(int argc, char const *argv[])
{
    // Iniclializar mutex

    pthread_mutex_init(&mutex,NULL);
    
    // Ingresar el numero de hilos
    int nH = atoi(argv[1]);
    q = atoi(argv[2]);

    // Vector de hilos
    pthread_t *h;
    h = (pthread_t*) malloc(nH * sizeof(pthread_t));

    if(nH < 1){
        perror("Error el numero de hilos debe ser mayor a uno");
        exit(EXIT_FAILURE);
    }

    // Creamos hilos

    for (int i = 0; i < nH; i++)
    {
        pthread_create(&h[i],NULL,&routineCounter,NULL);
    }
    
    // Realizamos join para esperar a que cada uno termine.

    for (int i = 0; i < nH; i++)
    {
        pthread_join(h[i],NULL);
    }


    printf("El contador tiene el siguiente valor: %d \n", c);

    // Destruir mutex
    pthread_mutex_destroy(&mutex);
    return 0;
}
