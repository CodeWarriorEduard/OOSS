#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUCKET_SIZE 10

int max = 0;

void *bucketSort(int arr[], int n){
    int buckets[BUCKET_SIZE][n];
    int bucketCounts[BUCKET_SIZE] = {0};

    int range  = (max + 1) / BUCKET_SIZE; 

    // Distribuir cada elemento.
    for (int i = 0; i < n; i++) {
        int bucketIndex = arr[i] / range;
        if (bucketIndex >= BUCKET_SIZE) { // Para valores exactamente iguales a max_value
            bucketIndex = BUCKET_SIZE - 1;
        }
        buckets[bucketIndex][bucketCounts[bucketIndex]++] = arr[i];
    }
    
    printf("Buckets:\n");
    for (int i = 0; i < BUCKET_SIZE; i++) { // Iterar sobre el número de buckets
        printf("Bucket %d: ", i);
        for (int j = 0; j < bucketCounts[i]; j++) { // Iterar sobre los elementos en el bucket
            printf("%d ", buckets[i][j]);
        }
        printf("\n");
    }
    
    
}

    
int findMaxValue(int arr[], int n){
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}

int main(int argc, char const *argv[])
{
    int v[]={29,25,3, 49, 9 , 37, 21, 43};
    max = findMaxValue(v, 8);
    bucketSort(v, 8);

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d ", v[i]);
    // }
    printf("\n");
    return 0;
}
