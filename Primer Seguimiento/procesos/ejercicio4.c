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

           if(i==1)
           {
            for (int j = 0; j < 2; j++)
            {
                childs[j] = fork();
                if(childs[j]>0) break;
                if(j==1){
                    for (int y = 0; y < 2; y++)
                    {
                        childs[y] = fork();
                        if(childs[y]==0) break;
                    }
                    
                }
                
            }
           } 

           break; 
        }
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
