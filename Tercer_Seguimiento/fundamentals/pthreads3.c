#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void *routine(){
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value;
    printf("Thread result %p \n", result);
    return (void*) result;
}


int main(int argc, char const *argv[])
{
    int *res;
    pthread_t t;
    if((pthread_create(&t,NULL,&routine, NULL))!=0){
        return 1;
    }

    //Esperar a que el hilo termine su ejecución antes de continuar
    // con el hilo que hizo la llamada.

    if((pthread_join(t, (void **)&res))!=0){
        return 2;
    }

    printf("Result %d \n",*res);
    printf("Result %d \n",res);
    free(res);
    return 0;
}
