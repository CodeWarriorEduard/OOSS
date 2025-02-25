#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int **A, **B, **C;

// Definir el struct para pasar las coordenadas

typedef struct resultado
{
    int r;
    int i;
    int j;

} resultado;

void showtree()
{
    char b[500];
    sprintf(b, "pstree -lp %d", getpid());
    system(b);
}

int main(int argc, char const *argv[])
{
    // 1) Verificar que se pueda multiplicar las matrices
    // 2) Asignar memoria a las matrices.
    // 3) Llenar las matrices.
    // 4) Crear los procesos.

    pid_t padre = getpid(), childs[3];

    // Tuberias

    int t[3][2];

    for (int i = 0; i < 3; i++)
    {
        pipe(t[i]);
    }

    // Definición de variables a usar

    A = B = C = NULL;
    int filaA, colA, filaB, colB, filaC, colC;
    printf("Digite el tamaño de la matriz 1 \n");
    printf("Fila Matriz 1>");
    scanf("%d", &filaA);
    printf("Columna Matriz 1>");
    scanf("%d", &colA);
    printf("Fila Matriz 2>");
    scanf("%d", &filaB);
    printf("Columna Matriz 2>");
    scanf("%d", &colB);

    // Verificar la validez de la multiplicacion.

    if (colA != filaB)
    {
        perror("No se pueden multiplicar las matrices \n");
        exit(1);
    }

    // columnas y filas resultantes.

    filaC = filaA;
    colC = colB;

    printf("Matriz resultante será de tamanio %d %d", filaC, colC);

    // Asignar memoria a matrices

    A = (int **)malloc(filaA * sizeof(int *));
    B = (int **)malloc(filaB * sizeof(int *));
    C = (int **)malloc(filaC * sizeof(int *));

    if (A == NULL || B == NULL || C == NULL)
    {
        perror("Error asignando memoria \n");
        exit(1);
    }

    for (int i = 0; i < filaA; i++)
    {
        A[i] = (int *)malloc(colA * sizeof(int));
    }

    for (int i = 0; i < filaB; i++)
    {
        B[i] = (int *)malloc(colB * sizeof(int));
    }

    for (int i = 0; i < filaC; i++)
    {
        C[i] = (int *)malloc(colC * sizeof(int));
    }

    // Llenar matriz A

    for (int i = 0; i < filaA; i++)
    {
        for (int j = 0; j < colA; j++)
        {
            A[i][j] = filaA * j + colA;
        }
    }

    // Llenar matriz B

    for (int i = 0; i < filaB; i++)
    {
        for (int j = 0; j < colB; j++)
        {
            B[i][j] = colB * i *filaA;
        }
    }

    // Mostrar matriz.
    printf("Matriz A \n");
    for (int i = 0; i < filaA; i++)
    {
        for (int j = 0; j < colA; j++)
        {
            printf("[%d] ", A[i][j]);
        }
        printf("\n");
    }

    printf("Matriz B \n");
    for (int i = 0; i < filaB; i++)
    {
        for (int j = 0; j < colB; j++)
        {
            printf("[%d] ", B[i][j]);
        }
        printf("\n");
    }

    resultado *r = NULL;
    ssize_t a = filaA*colB*sizeof(resultado);
    r = (resultado *)malloc(a);
    if (r == NULL)
    {
        perror("Error asignando memoria a r");
        exit(1);
    }
    // Creacion de procesos.
    int idxHijos;
    for (idxHijos = 0; idxHijos < 3; idxHijos++)
    {
        if ((childs[idxHijos] = fork()) == 0)
            break;
    }

    // Cerrar tuberías.
    if (idxHijos == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            close(t[i][1]);
        }

        // Operacion en el padre.
        int n, n2, n3;

        do
        {
            // Tuberia 1.
            n = read(t[0][0], r, a);
            printf("lectura de padre %d  %d %d %d\n", n, r->i, r->j, r->r);
            C[r->i][r->j] = r->r;
            // Tubería 2.
            n2 = read(t[1][0], r, a);
            printf("lectura de padre %d  %d %d %d\n", n, r->i, r->j, r->r);
            C[r->i][r->j] = r->r;
            // Tuberia 3.
            n3 = read(t[2][0], r, a);
            printf("lectura de padre %d  %d %d %d\n", n, r->i, r->j, r->r);
            C[r->i][r->j] = r->r;
        } while (n > 0 || n2 > 0 || n3 > 0);

        close(t[0][0]);
        close(t[1][0]);
        close(t[2][0]);


        // Imprimir matriz C
        for (int i = 0; i < filaA; i++)
        {
            for (int j = 0; j < colB; j++)
            {
                printf("[ %d ] ", C[i][j]);
            }

            printf("\n");
        }

        wait(NULL);
    }
    else if (idxHijos == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i != 0)
            {
                close(t[i][1]);
                close(t[i][0]);
            }
        }
        close(t[0][0]);

        // Operacion en el hijo 0.
        // Recorrer parte inferior de la matriz
        for (int i = 0; i < filaA; i++)
        {
            for (int j = i+1; j < colB; j++)
            {
                r->i = i;
                r->j = j;
                r->r = 0;
                for (int k = 0; k < colA; k++)
                {
                    r->r += (A[i][k] * B[k][j]);
                }
                // Enviar por pipe.
                write(t[0][1], r, a);
                printf("hola hijo 0 \n");
                printf("%d %d %d \n", i,j, r->r);
            }
        }
        close(t[0][1]);
    }
    else if (idxHijos == 1)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i != 1)
            {
                close(t[i][1]);
                close(t[i][0]);
            }
        }
        close(t[1][0]);
        // Operacion en el hijo 1.
        for (int i = 1; i < filaA; i++)
        {
            for (int j = 0; j < i; j++)
            {
                r->i = i;
                r->j = j;
                r->r = 0;
                for (int k = 0; k < colA; k++)
                {
                    r->r += (A[i][k] * B[k][j]);
                }
                // Enviar por pipe.
                write(t[1][1], r, a);
            }
        }
        close(t[1][1]);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            if (i != 2)
            {
                close(t[i][1]);
                close(t[i][0]);
            }
        }
        close(t[2][0]);

        // Operacion en el hijo 2.
        for (int i = 0; i < filaA; i++)
        {
            for (int j = 0; j < colB; j++)
            {
                r->i = i;
                r->j = j;
                r->r = 0;
                if (i == j)
                {
                    for (int k = 0; k < colA; k++)
                    {
                        r->r += (A[i][k] * B[k][j]);
                    }
                    // Enviar por pipe.
                    write(t[2][1], r, a);
                }
            }
        }
        close(t[2][1]);
    }

    if (padre == getpid())
    {
        showtree();
    }
    else
    {
        sleep(1);
    }
    return 0;
}
