#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>


int **bucket;
int *bucketCounts;
int BUCKET_SIZE;

// Mutex y barrera

pthread_mutex_t mutex;
pthread_barrier_t barrier;


typedef struct
{
    const char*filename;
    int bucketIndex;
}dataThread;



void initializeBuckets(int n){
    bucket = (int**) malloc(BUCKET_SIZE*sizeof(int*));
    bucketCounts = (int*) malloc(BUCKET_SIZE*sizeof(int));

    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        bucket[i] = (int*) malloc(n*sizeof(int));
        bucketCounts[i] = 0; 
    }
}



void *processBucket(void *arg){
    // Fase lectura

    pthread_mutex_lock(&mutex);
    dataThread *d = (dataThread*)arg;
    FILE *f = NULL;

    f = fopen(d->filename, "r");

    if(f==NULL){
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }

    int n;

    fscanf(f, "%d", &n); // Tamaño
    // Crear vector dinámico de tamaño n.

    int * vector;

    vector = (int*)malloc(n*sizeof(int));

    // Llenar vector con los valores del archivo

    for (int i = 0; i < n; i++)
    {
        fscanf(f, "%d", &vector[i]);
    }


    // Mostrar
    printf("Hilo %d \n", d->bucketIndex);
    for (int i = 0; i < n; i++)
    {
        printf("[%d] ", vector[i]);
    }
     
    int max = vector[0];
    for (int i = 1; i < n; i++)
    {
        if(vector[i] > max){
            max = vector[i];
        }
    }

    int range = (max+1)/BUCKET_SIZE; // calcular rango.

    for (int i = 0; i < n; i++)
    {
        int bucketIndex = vector[i]/range;
        if(bucketIndex>=BUCKET_SIZE){
            bucketIndex = BUCKET_SIZE - 1;
        }

        bucket[bucketIndex][bucketCounts[bucketIndex]++] = vector[i];
    }
    
    printf("\n");

    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        printf("Bucket %d :", i);
        for (int j = 0; j < bucketCounts[i]; j++)
        {
            printf("[%d] ", bucket[i][j]);
        }
        printf("\n");
    }
    pthread_mutex_unlock(&mutex);
    // Esperamos hilos a que lleguen a la barrera.
    pthread_barrier_wait(&barrier);
    // Fase ordenamiento

    
}




int main(int argc, char const *argv[])
{

    

    if(argc < 2){
        perror("Error");
        exit(EXIT_FAILURE);
    }

    int numArch = argc - 1;
    BUCKET_SIZE = numArch;
    initializeBuckets(1000);

    // Inicializar mutex y barrera.

    pthread_mutex_init(&mutex,NULL);
    pthread_barrier_init(&barrier, NULL, numArch);

    printf("%d \n", numArch);


    // Declarar hilos
    pthread_t *threads;

    threads = (pthread_t*)malloc(numArch*sizeof(pthread_t));
    dataThread data[numArch];
    for (int i = 0; i < numArch; i++)
    {
        data[i].filename = argv[i+1];
        data[i].bucketIndex = i;
        pthread_create(&threads[i],NULL, processBucket, &data[i]);
    }
    
    // Join

    for (int i = 0; i < numArch; i++)
    {
        pthread_join(threads[i], NULL);
    }
    

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);

    return 0;
}
