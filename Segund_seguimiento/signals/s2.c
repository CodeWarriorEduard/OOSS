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
    pid_t childs[5], padre = getpid(), subChild[2];
    int i,j;

    for (i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            if(i==0 || i==2){
               subChild[i/2] = fork();
               break;
            }
            break;
        };
    }
    
   
    
    
    if(padre==getpid()){
        usleep(100);
        char b[500];
        sprintf(b,"pstree -lp %d",getpid());
        system(b);
        printf("Proceso %d \n", getpid());
        Kill(childs[2], SIGUSR1);
        pause();
        printf("Proceso %d \n", getpid());
    }else{
        pause();
        printf("Proceso %d \n", getpid());
        if(i==2){
            if(subChild[1]){
                printf("Proceso %d \n", getpid());
                Kill(subChild[1], SIGUSR1);
                pause();
                printf("Proceso2 %d \n", getpid());
                Kill(childs[i-1], SIGUSR1);
            }else{
                Kill(getppid(), SIGUSR1);
            }
        }else if(i==0){
            if(subChild[0]){
                Kill(subChild[0], SIGUSR1);
                pause();
                printf("Proceso %d \n", getpid());
                Kill(getppid(), SIGUSR1);
            }else{
                Kill(getppid(), SIGUSR1);
            }
        }else{
            Kill(childs[i-1], SIGUSR1);
        }
    }

    
    return 0;
}

//  if(padre==getpid()){
//         usleep(100);
//         char b[500];
//         sprintf(b,"pstree -lp %d",getpid());
//         system(b);
//         printf("Proceso %d \n", getpid());
//         Kill(childs[2], SIGUSR1);
//         pause();
//         printf("Proceso %d \n", getpid());
//     }else{
//         pause();
//         printf("Proceso %d \n", getpid());
//         if(i==2){
//             if(subChild[0]){
//                 printf("Proceso %d \n", getpid());
//                 Kill(subChild[0], SIGUSR1);
//                 pause();
//                 printf("Proceso %d \n", getpid());
//                 Kill(childs[i-1], SIGUSR1);
//             }else{
//                 Kill(getppid(), SIGUSR1);
//             }
//         }else if(i==0){
//             if(subChild[1]){
//                 printf("Proceso %d \n", getpid());
//                 Kill(subChild[1], SIGUSR1);
//                 pause();
//                 printf("Proceso %d \n", getpid());
//             }else{
//                 Kill(getppid(), SIGUSR1);
//             }
//         }else{
//             Kill(childs[i-1], SIGUSR1);
//         }
//     };
