#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    pid_t padre = getpid(), childs[8];
    int i =0;
    int c = 0;

    for (i = 0; i <2; i++){
        childs[i] = fork();
        if(childs[i]==0){
            for (int j = 0; j < 2; j++)
            {
                childs[j] = fork();
                if(childs[j]==0){
                    if(j==1){
                        fork();
                    }
                    break;
                }
            }
            
            break;
        };
    }
    

    if(padre == getpid()){
        char b[500];
        sprintf(b, "pstree -lp %d", getpid());
        system(b);

    }else{
        sleep(1);
    }

    return 0;
}
