#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int c = 0;
int numI = 0;
void *routine(){
    printf("Hilo hará %d iteraciones \n", numI);
    for (int i = 0; i < numI; i++)
    {
        c++;
    }
    pthread_exit(0);
}


int main(int argc, char const *argv[])
{

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


    printf("El valor del contador es %d \n", c);
    
    return 0;
}
