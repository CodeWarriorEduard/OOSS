#include<unistd.h>
#include<stdio.h>

static int idata = 111;

int main(int argc, char const *argv[])
{
    int istack = 222;
    pid_t childPid;

    switch (childPid = fork())
    {
    case -1:
        printf("Error creando el proceso");    
        break;
    
    case 0:
        idata *=3; // Modificamos las variables del proceso hijo.
        istack *=3;
        break;


    default:
        sleep(3);
        break;
    }


   printf("PID=%ld %s idata=%d istack=%d\n", (long) getpid(),   (childPid == 0) ? "(child) " : "(parent)", idata, istack);

    return 0;
}
