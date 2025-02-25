#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
/*

Crear un programa con dos procesos que compartan un contador.

*/


int main(int argc, char const *argv[])
{
    
    pid_t    childs[2];
    int i;
    int *c;
    // Creacion de memoria compartida.
    int shm_size = sizeof(int);
    int shm_id;
    int n;
    shm_id = shmget(IPC_PRIVATE, 2*shm_size, IPC_CREAT|S_IRUSR| S_IWUSR);   

    c = (int*)shmat(shm_id, 0,0);

    c[0] = c[1] = c[2] = 0;

    printf("Ingresa el numero de iteraciones \n");
    scanf("%d", &n);

    for (i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0) break;
    }
    
    // Padre
    if(i==2){
        for (int j = 0; j < n; j++)
        {
            c[2] = c[2] + 1;
        }

        wait(NULL);
        wait(NULL);
        printf("Acumulado es: %d", c[0]+c[1]+c[2]);
        shmdt(c); // Desacoplar después de que los hijos terminen.
        shmctl(shm_id, IPC_RMID, 0);

    }else if (i==0)
    {
        for (int j = 0; j < n; j++)
        {
            c[0] = c[0] + 1;
        }
        shmdt(c);
    }else{
        for (int j = 0; j < n; j++)
        {
            c[1] = c[1] + 1;
        }
        shmdt(c);
    }
    



    return 0;
}
