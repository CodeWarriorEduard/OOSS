#include <stdio.h>      // Para funciones de entrada/salida como printf.
#include <stdlib.h>     // Para funciones de utilidad general como exit y system.
#include <sys/types.h>  // Para tipos de datos como pid_t.
#include <sys/wait.h>   // Para la función wait.
#include <unistd.h>     // Para la función fork y sleep.

// Función para mostrar el árbol de procesos actual.
void showtree() {
    char cmd[20] = {""};
    sprintf(cmd, "pstree -cAlp %d", getpid()); // Formatea el comando con el PID del proceso actual.
    system(cmd); // Ejecuta el comando en el shell.
}

int main(void) {
    pid_t root = getpid(), out; // Almacena el PID del proceso padre original y para la salida de wait.

    // Bucle para crear tres procesos hijos.
    for (int i = 0; i < 3; i++) {
        if (!fork()) { // Si es el proceso hijo...
            if (i%2 == 1) { // El primer y tercer hijo crean su propio hijo.
                if (!fork()){
                    execl("./triangulo", NULL);
                }else{
                    execl("./cuadrado", NULL);
                }
            }else{
                if (!fork()){
                    execl("./triangulo", NULL);
                    break;
                }
            }
        }
    }

    // El proceso padre muestra el árbol de procesos y espera a sus hijos.
    if (root == getpid()) {
        printf("circulo \n");
        sleep(1); // Espera un segundo para que se estabilice la creación de procesos.
        showtree(); // Muestra el árbol de procesos.
        // Espera a que terminen los tres hijos directos.
        for (int j = 0; j < 3; j++) {
            out = wait(NULL); // Espera a que un proceso hijo termine.
            printf("p:%d-w:%d\n", getpid(), out); // Imprime el PID del padre y del hijo que terminó.
        }
    } else {
        // Los procesos hijos esperan a sus hijos (si los tienen).
        out = wait(NULL);
        if (out != -1) {
            printf("p:%d-w:%d\n", getpid(), out); // Imprime el PID del hijo y de su hijo que terminó.
        }
        sleep(2); // Espera dos segundos.
    }

    return EXIT_SUCCESS; // Termina el proceso con éxito.
}