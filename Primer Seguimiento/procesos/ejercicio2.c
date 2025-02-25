#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

/* Crear un arbol de procesos p con tres hijos*/

int main(int argc, char const *argv[])
{
    pid_t childs[3] = {}, padre = getpid();

    for (int i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if(childs[i]==0) break;
        
    }


    if(padre==getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d" , getpid());
        system(b);
    }else{
        sleep(1);
    }

    printf("padre %d hijo %d \n",  getppid(), getpid());
    
    return 0;
}
