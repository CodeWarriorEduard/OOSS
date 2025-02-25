#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>



int main(int argc, char const *argv[])
{
    pid_t padre=getpid();
   
    for (int i = 0; i < 3; i++)
    {
        if(fork()>0)break;
        printf("Hola");
    }
    

    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);

    }else{
        sleep(1);
    }

    return 0;
}
