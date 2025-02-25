#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char const *argv[])
{
    pid_t childs[5], padre = getpid();


    for (int i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            
           for (int j = 0; j < i+1; j++)
           {
                if(fork()==0) break;
           }
           

            break;
        }
    }
    

    if(padre==getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);
    }else{
        sleep(1);
    }

    return 0;
}
