#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500

// Función para generar números aleatorios en un rango específico
int random_number(int min, int max) {
    return min + rand() % (max - min + 1);
}

void generate_matrix_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(1);
    }

    int matrixNivel[SIZE][SIZE];
    int matrixCalidad[SIZE][SIZE];
    int matrixPrediccion[SIZE][SIZE];

    // Semilla para números aleatorios
    srand(time(NULL));

    // Generar valores para las matrices y escribir en el archivo
    fprintf(file, "Matriz de Niveles (Capacidad, 0-100):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrixNivel[i][j] = random_number(0, 100);  // Nivel de capacidad entre 0 y 100
            fprintf(file, "%d ", matrixNivel[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    fprintf(file, "Matriz de Calidad (0: crítica, 1: regular, 2: óptima):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrixCalidad[i][j] = random_number(0, 2);  // Calidad entre 0 y 2
            fprintf(file, "%d ", matrixCalidad[i][j]);
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");

    fprintf(file, "Matriz de Predicción (Tendencia, -1: reducción, 0: estable, 1: aumento):\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            matrixPrediccion[i][j] = random_number(-1, 1);  // Predicción entre -1 y 1
            fprintf(file, "%d ", matrixPrediccion[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Archivo '%s' generado con éxito.\n", filename);
}

int main() {
    const char *filename = "matrices.txt";
    generate_matrix_file(filename);
    return 0;
}
