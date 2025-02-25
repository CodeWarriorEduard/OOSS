#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FILAS 6
#define COLUMNAS 8
#define NUM_HILOS 4  // Número de hilos, que se corresponderán con los cuadrantes

int matriz[FILAS][COLUMNAS];

// Estructura para almacenar los límites del bloque que cada hilo procesará
typedef struct {
    int inicioFila;
    int finFila;
    int inicioColumna;
    int finColumna;
    int id;
} DatosHilo;

// Función que cada hilo ejecutará para procesar su bloque
void *procesarBloque(void *arg) {
    DatosHilo *datos = (DatosHilo *)arg;

    // Imprimir las coordenadas del bloque que está procesando este hilo
    printf("Hilo %d procesando bloque desde (%d, %d) hasta (%d, %d)\n", datos->id, datos->inicioFila, datos->inicioColumna, datos->finFila, datos->finColumna);

    // Procesar el bloque de la matriz
    for (int i = datos->inicioFila; i < datos->finFila; i++) {
        for (int j = datos->inicioColumna; j < datos->finColumna; j++) {
            printf("Hilo %d procesando elemento matriz[%d][%d] = %d\n", datos->id, i, j, matriz[i][j]);
        }
    }

    free(datos);  // Liberar memoria para la estructura de datos
    pthread_exit(NULL);
}

int main() {
    // Inicializar la matriz con valores de ejemplo
    int contador = 1;
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            matriz[i][j] = contador++;
        }
    }

    pthread_t hilos[NUM_HILOS];  // Array de hilos

    // Determinar la cantidad de bloques por fila y por columna
    int bloquesPorFila = 2;  // Dividimos en 2 bloques por fila
    int bloquesPorColumna = 2;  // Dividimos en 2 bloques por columna

    // Crear los hilos para procesar los cuadrantes
    int hilo = 0;
    for (int i = 0; i < bloquesPorFila; i++) {
        for (int j = 0; j < bloquesPorColumna; j++) {
            DatosHilo *datos = malloc(sizeof(DatosHilo));
            
            // Calcular los límites del bloque que este hilo procesará
            datos->inicioFila = i * (FILAS / bloquesPorFila);  // Empieza en fila i
            datos->finFila = (i + 1) * (FILAS / bloquesPorFila);  // Termina en fila i+1
            if (i == bloquesPorFila - 1) {  // Último bloque en filas
                datos->finFila = FILAS;
            }

            datos->inicioColumna = j * (COLUMNAS / bloquesPorColumna);  // Empieza en columna j
            datos->finColumna = (j + 1) * (COLUMNAS / bloquesPorColumna);  // Termina en columna j+1
            if (j == bloquesPorColumna - 1) {  // Último bloque en columnas
                datos->finColumna = COLUMNAS;
            }

            datos->id = hilo++;  // Asignar un ID único al hilo

            // Crear el hilo
            pthread_create(&hilos[hilo - 1], NULL, procesarBloque, datos);
        }
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_HILOS; i++) {
        pthread_join(hilos[i], NULL);
    }

    return 0;
}

