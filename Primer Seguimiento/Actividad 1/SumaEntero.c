#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(int argc, char const *argv[])
{
    FILE * file;

    file = fopen(argv[1], "r");

    if(file == NULL){
        printf("Error al abrir el archivo");
        exit(1);
    }

    int size;
    int *array = NULL;

    fscanf(file, "%d", &size);

    array = (int*) malloc(size * sizeof(int));

    long int sum = 0;

    for (int i = 0; i < size; i++)
    {
        fscanf(file, "%d", &array[i]);
        sum += array[i];
    }
    

    // Hallar media de los datos

    double mean = sum/size; // DA RARO.

    // Hallar mediana

    int mediana;

    if(size%2==0){
        mediana = (array[size/2]+array[(size/2)+1])/2;
    }else{
        mediana = array[size/2];
    }

    printf("tamaño [%d]", size);
    printf("suma %ld, media %f \n", sum, mean);
    printf("%d %d \n", array[size/2], array[(size/2)+1]);
    printf("%d", array[size-1]);
    fclose(file);
    free(array);


    return 0;
}
