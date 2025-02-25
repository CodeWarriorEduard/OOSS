#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int main(int argc, char const *argv[])
{
    pid_t childs[12], padre=getpid();
    int status;
    for (int i = 0; i < 5; i++)
    {
        childs[i] = fork();
        if(childs[i]==0){

            if(i==2){
                for (int j = 0; j < 5; j++)
                {
                    childs[j]=fork();
                    if(childs[j]==0){
                        
                        if(j==0 || j==4){
                            fork();
                        }
                        break;
                    };
                }
                
            }

            break;
        };

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
