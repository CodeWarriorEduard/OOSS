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
    pid_t childs[2], padre = getpid();
    int i;

    for (i = 0; i < 2; i++)
    {
        if(!(childs[i] = fork())) break;
    }

    
    
    if(padre==getpid()){
        printf("\n");
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        printf("Padre %d \n", getpid());
        Kill(childs[1], SIGUSR1);
        pause();
        printf("Padre %d \n", getpid());
    }else{
        pause();
        printf("Hijo %d [%d] \n", i+1, getpid());
        if(i==1) Kill(childs[0], SIGUSR1);
        else Kill(getppid(), SIGUSR1);
    };

    
    return 0;
}

// if(i == 2){ // La última iteración corresponde al padre.
//         sleep(1);
//         printf("Padre %d", getpid());
//         Kill(childs[1], SIGUSR1);
//         pause();
//         printf("Padre %d", getpid());
//     }else{
//         pause();
//         printf("Hijo %d [%d]", i+1,getpid());
//         if(i==1) Kill(childs[0], SIGUSR1);
//         else Kill(getppid(), SIGUSR1);
//     }