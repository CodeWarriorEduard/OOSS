#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc, char const *argv[])
{
    pid_t childs[7], padre = getpid();

    for (int i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if(childs[i]==0){

            if(i==0){
                for (int j = 0; j < 3; j++)
                {
                    childs[j] = fork();
                    if(childs[j]==0) break;
                }
                
            }
            if(i==1){
               for (int k = 0; k < 2; k++)
               {
                    childs[k] = fork();
                    if(childs[k]==0) break;
               }
                
            }

            break;
        };

    }


    if(padre==getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d" , getpid());
        system(b);
    }else{
        sleep(1);
    }
    

    return 0;
}
