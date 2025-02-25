#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>



int main(int argc, char const *argv[])
{
    
    pid_t h, fatherP=getpid();
    int n;
    printf("Ingresa el valor de n: \n");
    scanf("%d", &n);
    printf("%d", n);
    for (int i = 0; i < n; i++)
    {
        h = fork();
        if(h==0) break;
    }
    

    if(fatherP == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
    }else{
        sleep(1);
    }

    return EXIT_SUCCESS;
}
