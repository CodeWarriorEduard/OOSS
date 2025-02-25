#include<stdio.h>
#include<stdlib.h>
#include<wait.h>
#include<unistd.h>
#include<signal.h>


void handler(int sig){}

void Kill(pid_t pid, int sig){
    usleep(1000);
    kill(pid, sig);
}


int main(int argc, char const *argv[])
{

    signal(SIGUSR1, handler);
    pid_t *childs, child, padre = getpid();
    int i;
    int n;

    printf("Ingresa el numero de procesos");
    scanf("%d", &n);
    if(n<3){
        perror("n should be more than 3");
        exit(1);
    }


    childs = (pid_t *) malloc(n * sizeof(pid_t));

    for (i = 0; i < n; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            
            if(i==n-1){
                child = fork();
            }

            break;
        }
    }
    

    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d \n", getpid());
        system(b);
        printf("Process %d \n", getpid());
        Kill(childs[n-1], SIGUSR1);
        pause();
        printf("Process %d \n", getpid());

    }else{
        pause();
        printf("Process %d \n", getpid());
        if(i==n-1){
            if(child){
                Kill(child, SIGUSR1);
                pause();
                printf("Process %d \n", getpid());
                Kill(childs[i-1], SIGUSR1);
            }else{
                Kill(getppid(), SIGUSR1);
            }
        }else if(i==0){
            Kill(getppid(), SIGUSR1);
        }else{
            Kill(childs[i-1], SIGUSR1);
        }
    }

    return 0;
}
