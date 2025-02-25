#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


pthread_mutex_t mutex;

/*

Un mutex es un mecanismo de sincronización de hilos, estos permiten que dos o más procesos concurrentes no ejecuten de forma simultanea una sección de 
código conocido como la sección critica.
El mutex bloquea la sección critica antes de usarla y después de usarla, la libera.

 1)Lo primero es definir una variable de tipo mutex pthread_mutex_t
 2) Inicializar el mutex usando pthread_mutex_init(&mutex, NULL);
 3) Utilizar las funciones de lock y unlock pasandoles como parámetro el mutex
 4) Por ultimo, destruir el mutex.

 */

long long int c = 0;
int numI = 0;
void *routine(){
    printf("Hilo %d hará %d iteraciones \n", getpid() ,numI);
    for (int i = 0; i < numI; i++)
    {
        pthread_mutex_lock(&mutex);
        c++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}


int main(int argc, char const *argv[])
{
    pthread_mutex_init(&mutex, NULL);
    int nT = atoi(argv[1]);
    numI = atoi(argv[2]);

    // Threads

    pthread_t ts[nT];


    for (int i = 0; i < nT; i++)
    {
        pthread_create(&ts[i], NULL, &routine, NULL);
    }

    for (int i = 0; i < nT; i++)
    {
        pthread_join(ts[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    printf("El valor del contador es %lld \n", c);
    
    return 0;
}
