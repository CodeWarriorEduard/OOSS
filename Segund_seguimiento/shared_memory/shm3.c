#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/wait.h>

#define ROWS 5
#define COLS 5

int main(int argc, char const *argv[])
{
    key_t key = ftok("shmfile", 65);

    int shmid = shmget(key, sizeof(int*) *ROWS * COLS, 0666 | IPC_CREAT);

    int (*m)[COLS] = shmat(shmid, (void*)0,0);


    if(fork() == 0){
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
        {
            m[i][j] = i*COLS+j;
        }
        }

        shmdt(m);
        exit(0);
        
    }else{
        wait(NULL);
        printf("Listo \n");
         for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
        {
           printf("[%d] ",  m[i][j]);
        }
        printf("\n");
        }
        shmdt(m);
        shmctl(shmid, IPC_RMID, NULL);
    }


    return 0;
}
