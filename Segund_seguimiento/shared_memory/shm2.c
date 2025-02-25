#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>

/*

Crea un programa con dos procesos hijos, donde cada uno imprimirá una letra

*/


int main(int argc, char const *argv[])
{
    pid_t childs[2];
    int i;
    int shm_size, shm_id;
    int *turno;

    shm_id = shmget(IPC_PRIVATE, shm_size, IPC_CREAT|S_IRUSR|S_IWUSR);

    turno = (int*) shmat(shm_id, 0,0);

    *turno = 0;

    for (i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if(childs[i] > 0) break;
    }
    

    while(*turno !=i);

    if(i==0){
        printf("A \n");
        *turno = *turno + 1;
        shmdt(turno);
    }else if (i==1)
    {
        printf("B \n");
        *turno = *turno + 1;
        shmdt(turno);
       
    }else{
        printf("C \n");
        *turno = *turno + 1;
        wait(NULL);
        wait(NULL);
        shmdt(turno);
        shmctl(shm_id, IPC_RMID, 0);
    }
    




    return 0;
}
