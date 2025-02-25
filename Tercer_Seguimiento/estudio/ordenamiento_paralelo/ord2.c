#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int **bucket;
int *bucketCount;
int bucketSize;

//MUTEX Y BARRERA

pthread_mutex_t mutex;

pthread_barrier_t barrier;


typedef struct{
    const char*filename;
    int id;
}ThreadData;


/*

APRENDER ALGORITMO DE BUCKET

*/

// Inicializar vector y matriz para los casilleros

void initializeBucket(int n){
    bucket =(int**) malloc(bucketSize*sizeof(int*)); // Matriz.
    bucketCount = (int*)malloc(bucketSize*sizeof(int));
    for (int i = 0; i < bucketSize; i++)
    {
        bucket[i] = (int*) malloc(n*sizeof(int));
        bucketCount[i] = 0;
    }
    
}
// Copiar este sorting en algun lado.
void sortBucket(int *bucket, int count) {
    for (int i = 1; i < count; i++) {
        int key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j = j - 1;
        }
        bucket[j + 1] = key;
    }
}

void *processBucket(void *arg){

    ThreadData *d = (ThreadData*)arg;

    printf("Hilo %d procesando archivo %s\n", d->id, d->filename);
    pthread_mutex_lock(&mutex);
    // Definir puntero al archivo
    FILE *f = NULL;

    f = fopen(d->filename, "r");

    if(f==NULL){
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    // Leer tamaño y crear vector dinámico

    int sizeVector;
    fscanf(f, "%d", &sizeVector);

    
    int *vec = (int*)malloc(sizeVector*sizeof(int));

    // // Llenar vector

    for (int i = 0; i < sizeVector; i++)
    {
        fscanf(f, "%d", &vec[i]);
    }
    
    // Mostrar archivo
      for (int i = 0; i < sizeVector; i++)
    {
       printf("[%d]", vec[i]);
    }
    printf("\n");

    // Encontrar mayor para bucket
    int max = vec[0];
    for (int i = 1; i < sizeVector; i++)
    {
        if(vec[i]> max){
            max = vec[i];
        }
    }
    
    int range = (max+1)/bucketSize;

    for (int i = 0; i < sizeVector; i++)
    {
        int bucketIndex = vec[i]/range;
        if(bucketIndex>=bucketSize){
            bucketIndex = bucketSize - 1;
        }
        bucket[bucketIndex][bucketCount[bucketIndex]++] = vec[i];
    }
    pthread_mutex_unlock(&mutex);
     printf("\n");

    pthread_barrier_wait(&barrier);
    // for (int i = 0; i < bucketSize; i++)
    // {
    //     printf("Bucket %d :", i);
    //     for (int j = 0; j < bucketCount[i]; j++)
    //     {
    //         printf("[%d] ", bucket[i][j]);
    //     }
    //     printf("\n");
    // }

    // Fase ordenamiento
    printf("\n");
    sortBucket(bucket[d->id], bucketCount[d->id]);
    for (int i = 0; i < bucketSize; i++)
    {
        printf("Bucket %d :", i);
        for (int j = 0; j < bucketCount[i]; j++)
        {
            printf("[%d] ", bucket[i][j]);
        }
        printf("\n");
    }

}

int main(int argc, char const *argv[])
{

    if(argc < 2){
        perror("At least one file");
        exit(EXIT_FAILURE);
    }

    int numFiles = argc - 1;
    bucketSize = numFiles;
    initializeBucket(1000);

    // Inicializar mutex y barrera

    pthread_mutex_init(&mutex,NULL);
    pthread_barrier_init(&barrier, NULL, numFiles);

    // Numero de hilos y buckets debe ser igual al numero de archivos

    ThreadData data[numFiles];

    // Crear hilos

    pthread_t *threads;
    threads=(pthread_t*)malloc(numFiles*sizeof(pthread_t));

    for (int i = 0; i < numFiles; i++)
    {
        data[i].filename = argv[i+1];
        data[i].id = i;
        pthread_create(&threads[i], NULL, processBucket, &data[i]);
    }
    

    //Join 

    for (int i = 0; i < numFiles; i++)
    {
        pthread_join(threads[i],NULL);
    }

    // Arreglo resultante
    int numElements = 0;

    for (int i = 0; i < bucketSize; i++)
    {
        numElements+=bucketCount[i];
    }


    int *sorted = (int*)malloc(numElements*sizeof(int));
    int index = 0;
    for (int i = 0; i < bucketSize; i++)
    {
        for (int j = 0; j <bucketCount[i]; j++)
        {
            sorted[index++] = bucket[i][j];
        }
        
    }
    


    printf("%d", numElements);
    
    
    printf("Sorted array \n");

    for (int i = 0; i < numElements; i++)
    {
        printf("[%d] ", sorted[i]);
    }

    // Destroy mutex and barrier

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);


    return 0;
}
