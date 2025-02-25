#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

/*

BUSQUEDA EN PARALELO

*/
// Mutex

pthread_mutex_t mutex;
int *e;
int c;
int target;
int *pos;
int index = 0;
// Struct para dividir  vector

typedef struct divi
{   
    int inicio, final;
    int id;
}divi;


void *routine(void * args){
    divi *d = (divi*)args;
    printf("Hilo %d recorrerá desde %d a %d \n", d->id, d->inicio, d->final);
    for (int i = d->inicio; i < d->final; i++)
    {
        pthread_mutex_lock(&mutex);
        if(e[i]== target){
            c++;
            pos[index++] = i;
        }
        pthread_mutex_unlock(&mutex);
    }   
}


int main(int argc, char const *argv[])
{
    // Leer archivo

    FILE *f = NULL;

    f = fopen(argv[2], "r");

    if(f==NULL){
        perror("Error reading file");
        exit(1);
    }


    int nElementos;

    fscanf(f, "%d", &nElementos);

    // Target 

    target = atoi(argv[3]);

    // Vector dinámico

    e = (int*) malloc(nElementos * sizeof(nElementos));

    // Almacenar posiciones

    pos = (int*) malloc(nElementos * sizeof(nElementos));


    for (int i = 0; i < nElementos; i++)
    {
        fscanf(f, "%d", &e[i]);
    }
    

    // Mostrar elementos del vector

    for (int i = 0; i < nElementos; i++)
    {
        printf("%d ", e[i]);
    }
    
    printf("\n");
    // Inicializar mutex

    pthread_mutex_init(&mutex, NULL);

    int nHilos = atoi(argv[1]);
    pthread_t *threads;

    threads = (pthread_t*) malloc( nHilos * sizeof(pthread_t));

    if(nHilos > nElementos){
        perror("Error the number of threads must be less or equial to the number of elements");
        exit(1);
    }


    // Dividir el vector entre los hilos.

    int nEByH = nElementos / nHilos;

    // Crear hilos

    for (int i = 0; i < nHilos; i++)
    {
        divi *vDiv = malloc(sizeof(div));
        vDiv->inicio = i * nEByH;
        vDiv->final = (i==nHilos-1)? nElementos: (i+1)*nEByH;
        vDiv->id = i;
        pthread_create(&threads[i], NULL, routine, vDiv);
    }
    

    //Join 

     for (int i = 0; i < nHilos; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    printf(" Apariciones de %d %d veces \n", target, c);

    // Posiciones

    for (int i = 0; i < index; i++)
    {
        printf("%d apareció en la posición %d \n", target, pos[i]);
    }
    

    pthread_mutex_destroy(&mutex);

    return 0;
}
