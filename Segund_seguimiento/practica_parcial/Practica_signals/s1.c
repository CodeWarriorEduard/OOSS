#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/types.h>


void handler(int sig){}

void showtree(){
    char b[500];
    sprintf(b, "pstree -lp %d", getpid());
    system(b);
}

void Kill(pid_t pid, int sig){
    usleep(100);
    kill(pid, sig);
}

int main(int argc, char const *argv[])
{

    signal(SIGUSR1, handler);

    pid_t childs[3], child, padre=getpid();
    int i;
    for (i = 0; i < 3; i++)
    {
        if(( childs[i] = fork())==0){
            if(i==0 || i==2){
                child = fork();
            }
            break;
        }
    }
    
    if(padre == getpid()){
        showtree();
        printf("Process %d \n", getpid());
        Kill(childs[2], SIGUSR1);
        pause();
        printf("Process %d \n", getpid());
    }else{
        pause();
        printf("Process %d \n", getpid());
        if(i==2){
            if(child) {// padre
                Kill(child, SIGUSR1);
                pause();
                printf("Process %d \n", getpid());
                Kill(childs[i-1], SIGUSR1);
            }else{
                //Hijo
                Kill(getppid(), SIGUSR1);
            }
        }else if (i==0)
        {
            if(child) {// padre
                Kill(child, SIGUSR1);
                pause();
                printf("Process %d \n", getpid());
                Kill(getppid(), SIGUSR1);
            }else{
                //Hijo
                Kill(getppid(), SIGUSR1);
            }
        }else{
            Kill(childs[i-1], SIGUSR1);
        }
        
    }

    return 0;
}
