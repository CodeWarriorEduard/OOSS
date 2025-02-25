#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

void showtree(){
    char b[500];
    sprintf(b, "pstree -lp %d", getpid());
    system(b);
}


int main(int argc, char const *argv[])
{
    pid_t padre = getpid(), childs[3];
    int i, flag;
    int t[4][2];
    char buffer[2];

    for (int i = 0; i < 4; i++)
    {
        pipe(t[i]);
    }
    


    for (i = 0; i < 3; i++)
    {
        if((childs[i] = fork())==0)break;
    }

    if(i==3){

        printf("hola padre %d", getpid());
        flag = 1;
        for (int i = 0; i < 4; i++)
        {
            if(i!=0 && i!=3){
                printf("padre %d \n", i);
                close(t[i][0]);
                close(t[i][1]);
            }
        }
        close(t[0][0]);
        close(t[3][1]);

        write(t[0][1], "A", 1);

        // Leer del ultimo proceso.
        int n = read(t[3][0], buffer, sizeof(buffer));
        if(n>0){
            printf("%s \n",buffer);
        }
        wait(NULL);
        
    }else if (i==0)
    {
        flag = 2;
        for (int i = 0; i < 4; i++)
        {
            if(i!=0 && i!=1){
                close(t[i][0]);
                close(t[i][1]);
            }
        }
        close(t[1][0]);
        close(t[0][1]);
        int n = read(t[0][0], buffer, sizeof(buffer));
        if(n>0){
            printf("%s \n",buffer);
            write(t[1][1], "B", 1);
        }
    }else if (i==1)
    {
        flag = 3;
        for (int i = 0; i < 4; i++)
        {
            if(i!=1 && i!=2){
                close(t[i][0]);
                close(t[i][1]);
            }
        }
        close(t[1][1]);
        close(t[2][0]);
        int n = read(t[1][0], buffer, sizeof(buffer));
        if(n>0){
            printf("%s \n",buffer);
            write(t[2][1], "C", 1);
        }
    }else{
        flag = 4;
        for (int i = 0; i < 4; i++)
        {
            if(i!=2 && i!=3){
                close(t[i][0]);
                close(t[i][1]);
            }
        }
        close(t[2][1]);
        close(t[3][0]);
        int n = read(t[2][0], buffer, sizeof(buffer));
        if(n>0){
            printf("%s \n",buffer);
            write(t[3][1], "D", 1);
        }
    }





    if(padre == getpid()){
        showtree();
    }else{
        sleep(1);
    }

    return 0;
}
