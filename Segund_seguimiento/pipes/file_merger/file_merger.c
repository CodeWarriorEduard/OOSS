#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    pid_t childs[2], root = getpid();
    int i;

    int fd[2], fd2[2];

    pipe(fd);
    pipe(fd2);


    for (i = 0; i <2; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0) break;
    }

    if(i==2){ // padre.
        close(fd[1]);
        close(fd[0]);
        close(fd2[1]);
    }else{
        if(i==0){ // hijo 1
            close(fd2[1]);
            close(fd2[0]);
            close(fd[0]); 

            // Leer archivos



        }else{ // hijo 2
            close(fd[1]);
            close(fd2[0]); 
        }
    }

    if(root == getpid()){
        char b[400];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
    }else{
        sleep(1);
    }
    


    return 0;
}
