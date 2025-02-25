#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t childs[14], padre = getpid();

    if(fork()){
        fork();
       if(!fork()){
        execl("/os-unimag/Primer Seguimiento/procesos/parcial/execEjercicio", NULL);
       }else{
            if(!fork()){
                execl("./execEjercicio/circulo", NULL);
            }
       }
        
    }
    fork();

    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);

    }else{
        sleep(1);
    }

    return 0;
}
