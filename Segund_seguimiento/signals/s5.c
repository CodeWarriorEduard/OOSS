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
    pid_t childs[5], padre = getpid(), child[2];
    int i,j = 0;

    for (i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            if(i==0 || i==1){
                child[j] = fork();
                j++;
            }
            break;
        };
    }

    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);

        // Signal
        printf("Proceso %d \n", getpid());
        Kill(childs[1], SIGUSR1);
        pause();
        printf("Proceso %d \n", getpid());
    }else{
        pause();
        printf("Proceso %d \n", getpid());
        if(i==1){
            if(child[0]){
                Kill(child[0], SIGUSR1);
                pause();
                printf("Proceso %d \n", getpid());
                Kill(childs[i-1], SIGUSR1);
            }else{
                Kill(getppid(), SIGUSR1);
            }
        }else{
            if(child[0]){
                Kill(child[0], SIGUSR1);
                pause();
                printf("Proceso %d \n", getpid());
                Kill(getppid(), SIGUSR1);
            }else{
                Kill(getppid(), SIGUSR1);
            }
        }
    }

    return EXIT_SUCCESS;
}