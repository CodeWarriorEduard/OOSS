#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int turno = 0;

void *routineImpresora(void *arg)
{
    pthread_mutex_lock(&mutex);
    int id = *(int *)arg;
    while (turno != id) // Si la condicion no está lista, se espera al hilo
    {
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Hilo %d Imprimiendo en papelería \n", id);

    turno++;
    if (turno > 2) turno = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[])
{

    pthread_t h[3];

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < 3; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&h[i], NULL, &routineImpresora, id);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(h[i], NULL);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);

    return 0;
}
