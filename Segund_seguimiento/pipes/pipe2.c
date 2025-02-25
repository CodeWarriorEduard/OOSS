/*
Ejercicio 1: Comunicación entre dos procesos con pipes
Crea un script en bash que haga lo siguiente:
Un proceso hijo genera números aleatorios entre 1 y 100.
El proceso hijo envía esos números al proceso padre usando un pipe.
El proceso padre recibe los números y los imprime en pantalla.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<time.h>
// ¿Cómo trabajo dentro de un proceso en específico?


int generateNumber(){
    return rand() % 10 + 1;
}

int main(int argc, char const *argv[])
{
    pid_t hijo, padre = getpid();
    int fd[2], n, l;

    pipe(fd);

    hijo = fork();
    if(hijo==0){
        int x = generateNumber();
        printf("Estamos en el hijo: [%d], escribimos x: %d \n", getpid(), x);
        write(fd[1], &x, sizeof(x)); // fd[1] Write, Dirección y tamaño de x.
    }else{
        n = read(fd[0], &l, sizeof(n));
        printf("Estamos en el padre: [%d], leemos x: %d \n", getpid(), l);

    }


    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
    }else{
        sleep(1);
    }
    
    return 0;
}

