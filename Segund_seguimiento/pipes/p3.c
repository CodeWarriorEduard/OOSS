#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>


int main(int argc, char const *argv[])
{
    pid_t childs[2], padre = getpid();
    int i;

    int fd[2], fd1[2];


    // Entero generado.
    int n;

    pipe(fd);
    pipe(fd1);

    for (i = 0; i < 2; i++)
    {
        if(!(childs[i]=fork())){
            break;
        }
    }
    

    // Cerrar escritura del padre.

    if(i==2){
        close(fd[1]);
        close(fd1[1]);

        // Leer dato de los hijos

        int a,b;

        read(fd[0], &a, sizeof(a));
        read(fd1[0], &b, sizeof(b));

        printf("Numeros leidos: [%d] [%d] \n",a,b);

        printf("Sumatoria de los procesos hijos: %d \n", a+b);

    }else{
        if(i==1){ // Cerrar comunicaciones de tuberias con procesos hijos.
            close(fd[0]);
            close(fd[1]);
            close(fd1[0]);
            // Entero random 1.

            n = rand()%1000;
            write(fd1[1], &n, sizeof(n));

        
        }else{
            close(fd1[0]);
            close(fd1[1]);
            close(fd[0]);
            // Entero random 2.
            n = rand()%1000;
            write(fd[1], &n, sizeof(n));
        }
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

