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
    pid_t childs[3], padre = getpid(), nieto, bisnieto, bisHijo1, bisHijo2;
    int t[11][2];
    int idxHijo, jdxHijo, kdxHijo, esNieto;
    for (idxHijo = 0; idxHijo < 3; idxHijo++)
    {
        childs[idxHijo] = fork();
        if(childs[idxHijo]==0){
            if(idxHijo == 1){             
               nieto = fork();
               if(nieto==0){
                esNieto = 1;
                    bisnieto = fork();
                    if(bisnieto==0){
                        bisHijo1=fork();
                        if(bisHijo1>0){
                            bisHijo2 = fork();
                        }
                    }
               }
                
            }
            break;
        }
    }
    



    if(padre == getpid()){
        showtree();

        // Cerrar tuberias del padre.

        for (int i = 0; i < 11; i++)
        {
            if(i!=0 || i!=10){
                close(t[i][0]);
                close(t[i][1]);
            }
        }

        close(t[0][0]);
        close(t[10][1]);
        

    }else{
        sleep(1);
        
        if(esNieto){
            printf("soy el nieto %d", getpid());
        }
        
        if(idxHijo == 0){
            for (int i = 0; i < 11; i++)
            {
                if(i!=9 || i!=10){
                    close(t[i][0]);
                    close(t[i][1]);
                }
            }
        close(t[9][0]);
        close(t[10][1]);
            
        }
        if(idxHijo == 1){
            for (int i = 0; i < 11; i++)
            {
                if(i!=1 || i!=2 || i!=10){
                    close(t[i][0]);
                    close(t[i][1]);
                }
            }
            close(t[1][0]);
            close(t[2][1]);
            close(t[10][0]);
          
         
        }
        if(idxHijo == 2){
            for (int i = 0; i < 11; i++)
            {
                if(i!=0|| i!=1){
                    close(t[i][0]);
                    close(t[i][1]);
                }
            }
            close(t[0][1]);
            close(t[1][0]);
        }

    }
    return 0;
}
