#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    pid_t childs[8], padre = getpid();

    for (int i = 0; i < 10; i++)
    {
        childs[i] = fork();
        if(childs[i]==0){
            if(i==9){  
                for (int j = 0; j < 5; j++)
                {
                    childs[j] = fork();
                    if(childs[j]==0) break;
                }
                
            }
            break;
        };
        
    }

    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d",getpid());
        system(b);
    }else{
        sleep(1);
    }
    
    return 0;
}
