#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

// Crear vector y matriz global para que pueda ser accedido por los hilos

typedef struct h
{
    int ini, final;
    int id;

}divisionFila;


typedef struct h2
{
    int i;
    int val;
}values;

int **matriz;
int *vector;
int m, n;
values *val;

pthread_mutex_t mutex;


void *processVector(void *arg){

    divisionFila *filaHilo = (divisionFila*)arg;
    for (int i = filaHilo->ini; i < filaHilo->final; i++)
    {
        val[i].i = 0;
        for (int j = 0; j < n; j++)
        {
            pthread_mutex_lock(&mutex);
            val[i].val += vector[j] * matriz[i][j];
            pthread_mutex_unlock(&mutex);
        }
        val[i].i = i;
    }

    free(filaHilo);
    

    return NULL;
}

int main(int argc, char const *argv[])
{

    pthread_mutex_init(&mutex, NULL);

    // Tamaño Matriz y vector
    m = atoi(argv[1]); // Filas
    n = atoi(argv[2]); // Columnas


    // Inicializar matriz dinámica de tamaño mxn

    matriz = (int**)malloc(m*sizeof(int*));
    for (int i = 0; i < m; i++)
    {
        matriz[i] = (int*)malloc(n*sizeof(int)); 
    }

    // Llenar matriz con valores aleatorios

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz[i][j] = rand() % 100 + 1;
        }
        
    }
    
     for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("[%d] ", matriz[i][j]);
        }
        printf("\n");
        
    }
    
    // Inicializar vector dinámico
    printf("\n");
    vector = (int*) malloc(n*sizeof(int));
    for (int i = 0; i < n; i++)
    {
       vector[i] = rand() % 100 + 1;
    }

      for (int i = 0; i < n; i++)
    {
        printf("[%d] ", vector[i]);
        
    }

    printf("\n");
    // Vector de resultados de tamaño n.

    val = (values*) malloc(m*sizeof(values));

     if(val == NULL){
        perror("Error asignando memoria");
        exit(1);
    }



    // Hilos
    int numThreads = atoi(argv[3]);
    pthread_t *threads;

    threads = (pthread_t*)malloc(numThreads*sizeof(pthread_t));

    if(threads == NULL){
        perror("Error asignando memoria");
        exit(1);
    }


    // Dividir por filas 

    int filasXHilo = m/numThreads;

    // Crear hilos

    for (int i = 0; i < numThreads; i++)
    {
        divisionFila *d = malloc(sizeof(divisionFila));
        d->ini = i*filasXHilo;
        d->final= (i==numThreads -1 )? m:(i+1)*filasXHilo;
        d->id = i;
        pthread_create(&threads[i], NULL, &processVector, d);
    }
    
    // Join 

    for (int i = 0; i < numThreads; i++)
    {
        pthread_join(threads[i], NULL);
    }


    // Visualizar vector resultante

    for (int i = 0; i < n; i++)
    {
        printf("%d %d ", val[i].i, val[i].val);
    }
    printf("\n");
    
    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < m; i++) {
    free(matriz[i]);
    }
    // No olvides liberar

    return 0;
}
