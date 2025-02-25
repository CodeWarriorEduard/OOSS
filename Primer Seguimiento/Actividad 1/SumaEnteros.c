#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

/* *******************************************************************/
// Tupla para guardar el dato y su frecuencia
typedef struct tuple{
    int key;
    int value;
}Tuple;



double findMediana(int * array, int size){

    if(size%2==0){
        return (array[(size/2)] + array[(size/2)+1])/2;
    }
    return array[size/2];
}

//  Quick sort


void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}


int partition(int *array, int bottom, int top){
    int pivote = array[top];

    int i = bottom - 1;

    for (int j = bottom; j <= top -1; j++)
    {
        if(array[j]<pivote){
            i++;
            swap(&array[i],&array[j]);
        }
    }

    swap(&array[i+1], &array[top]);
    return i+1;
    
}


void quickSort(int* array, int bottom, int top){
    if(bottom<top){
        int pi = partition(array, bottom, top);
        quickSort(array, bottom, pi-1);
        quickSort(array, pi+1, top);
    }
}



Tuple * obtenerModa(int *arr, int n){
    
    int maxVal = 0, valKey=0;
    int count = 0;

    Tuple *tuple = (Tuple*) malloc(sizeof(Tuple));

    for (int i = 0; i < n; i++){
        if(arr[i] == arr[i-1]){
            count++;
        }else{
            if(count>maxVal){
                maxVal = count;
                valKey = arr[i-1];
            }
            count = 1;

        }
    }
    
    if(count>maxVal){
        maxVal = count;
        valKey = arr[n-1];
    }

    tuple->key = valKey;
    tuple->value = maxVal;

    return tuple;

}



/* *******************************************************************/


int main(int argc, char const *argv[])
{
    // Medimos el tiempo computacional usando la función clock_gettime
    // de la librería time.h

    struct timespec start, end;
    double elapsedReading, elapsedSum,elapsedModa, elapsedVarianza, elapsedDes, elapsedMedian ,frequencyStimation = 0;


    clock_gettime(CLOCK_REALTIME, &start);

    FILE * file;
    file = fopen(argv[1], "r");

    if(file == NULL){
        printf("Error al abrir el archivo");
        exit(1);
    }

    int size;
    int *array = NULL;

    fscanf(file, "%d", &size);

    array = (int *) malloc(size*sizeof(int));

    long int sum = 0;

    clock_gettime(CLOCK_REALTIME, &end);
    elapsedReading = ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9);

    // Almacenar el contenido de archivo en memoria.
    clock_gettime(CLOCK_REALTIME, &start);
    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%d", &array[i]);
        sum+= array[i];
    }
    
    clock_gettime(CLOCK_REALTIME, &end);
    elapsedSum = ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9);


    /**************/
    // Ordenamiento de datos para facilitar la busqueda de moda y mediana.
    quickSort(array, 0, size-1);
    /*************/

    // Hallar media de los datos (PARA HALLAR LA VARIANZA).

    double mean = sum/size;

    // Hallar mediana de los datos
    
    double mediana = findMediana(array, size);

    // Calculo de la varianza

    clock_gettime(CLOCK_REALTIME, &start);
    long int sumatoria = 0;

    for (int i = 0; i < size; i++)
    {
        sumatoria+= pow((array[i] - mean), 2);
    }
    
    double varianza = sumatoria/size; 

    clock_gettime(CLOCK_REALTIME, &end);
    elapsedVarianza = ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9);

    /****************************************/
    
    // Hallar la desviacion estandar

    clock_gettime(CLOCK_REALTIME, &start);

    sumatoria = 0; // Reiniciamos la sumatoria a 0.

    for (int i = 0; i < size; i++)
    {
        sumatoria+= pow((array[i] - mean), 2);
    }
    
    double desviacion = sqrt(sumatoria/size); 

    clock_gettime(CLOCK_REALTIME, &end);
    elapsedDes = ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9);

    /****************************************/
    // Moda en los datos de los archivos.
    clock_gettime(CLOCK_REALTIME, &start);
    Tuple *tuple = obtenerModa(array, size);

    clock_gettime(CLOCK_REALTIME, &end);
    elapsedModa = ((end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec)/1e9);
   
    
    /****************************************/

    printf("Archivo [%s] abierto \n reading_file_time:  %f seg \n  sum_time: %f seg \n sum: %ld \n", argv[1], elapsedReading, elapsedSum , sum);
    printf("median_time: %f seg \n variance_time  %f seg \n Desviation_time %f seg \n", elapsedMedian, elapsedVarianza, elapsedDes);
    printf("Mean of data %f \n Median: %f \n Variance %f \n Desviation %f \n", mean, mediana, varianza, desviacion);
    printf("Mode_time %f \n Mode: (%d, %d) \n", elapsedModa, tuple->key, tuple->value);
    fclose(file);
    free(array);


    return 0;
}
