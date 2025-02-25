#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig){}

void Kill(pid_t pid, int s){
    usleep(100);
    kill(pid, s);
}

/* Las señales SIGUSR1 y SIGUSR2 son señales del usuario, estas son generadas por el sistema operativo.*/

int main(int argc, char const *argv[])
{
    system("clear");

    signal(SIGUSR1, handler);
    pid_t childs[5], padre = getpid();
    int i;

    for (i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            break;
        };
    }

    int c = 0;

    while(c<3){
        if(padre==getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
        printf("Proceso %d \n", getpid());
        Kill(childs[1], SIGUSR1);
        pause();
        printf("Proceso %d \n", getpid());
        }else{
        pause();
        if(i==1){
            printf("Proceso %d \n", getpid());
            Kill(childs[i-1], SIGUSR1);
        }else{
            printf("Proceso %d \n", getpid());
            Kill(getppid(), SIGUSR1);
        }
        }
        c++;
        sleep(2);
    }

    return EXIT_SUCCESS;
}