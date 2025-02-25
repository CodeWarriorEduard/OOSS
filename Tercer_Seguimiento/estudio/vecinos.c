#include <stdio.h>
#include <stdlib.h>

#define FILAS 5
#define COLUMNAS 5

int **matriz;

void vecinos(int x, int y)
{

    for (int i = -1; i <=1; i++)
    {
        for (int j = -1; j <=1; j++)
        {
            if(i==0 && j==0) continue;

            int nx = x+i;
            int ny = y+j;
            if(nx>=0 && nx<FILAS && ny>=0 && ny<COLUMNAS){
                printf("Vecino en %d %d: %d \n",nx,ny,matriz[nx][ny]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{

    // Matriz en malloc

    matriz =(int**) malloc(FILAS*sizeof(int*));

    for (int i = 0; i < FILAS; i++)
    {
        matriz[i] = (int*) malloc(COLUMNAS*sizeof(int));
    }
    
    // Llenamos la matriz.
    int c = 0;
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            matriz[i][j] = c++;
        }
        
    }

    // Mostramos la matriz.
    
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            printf("[%d] ", matriz[i][j]);
        }
        printf("\n");
    }
    

    vecinos(3,4);

    return 0;
}
