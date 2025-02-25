#include<stdio.h>

int main(int argc, char const *argv[])
{
    int arr[2] = {41,3};
    int size = sizeof(arr)/sizeof(arr[0]);
    int c = size - 1;
    int temp = arr[0];

     // Imprimimos el array.
    for (int i = 0; i < size; i++)
    {
       printf("[%d]", arr[i]);
    }

    for (int i = 0; i < size/2; i++)
    {    
        temp = arr[i];
        arr[i] = arr[c];
        arr[c] = temp;
        c--;
    }

    // Imprimimos el array.
    printf("\n");
    for (int i = 0; i < size; i++)
    {
       printf("[%d]", arr[i]);
    }

    printf("\n");

    return 0;
}
