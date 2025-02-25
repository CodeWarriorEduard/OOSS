#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


// Crear 4 procesos uno debajo del otro. padre, hijo, nieto, bisnieto.

int main(int argc, char const *argv[]){
    pid_t pid;
    int i;
    
    for (i = 0; i < 3; i++)
    {
        pid = fork();
        if(pid>0) break;
    }
    

   
    
    printf("Padre %d saliendo -- creo hijo  %d\n", getpid(), pid);
    exit(0);


    return 0;
}
