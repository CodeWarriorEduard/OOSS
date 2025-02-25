#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
void showtree(){
    char b[500];
    sprintf(b, "pstree -lp %d", getpid());
    system(b);
}

char *letterToSend(int flag){
    
    char *a = NULL;
    if(flag == 0){
        a = "a-";
    }if (flag == 1)
    {
        a = "d-";
    }if (flag == 2)
    {
        a = "g-";
    }if (flag == 3)
    {
        a = "i-";
    }if (flag == 4)
    {
        a = "c-";
    } if (flag == 5)
    {
        a = "f-";
    } if (flag == 6)
    {
        a = "b-";
    } if (flag == 7)
    {
        a = "e-";
    } if(flag == 8) {
        a = "h-";
    }
    
    return a;
    
}

int main(int argc, char const *argv[])
{
    pid_t childs[3], nietos[3], bisnieto1, padre = getpid();
    int i;


    // Crear tuberias
    int numPipes = 14;
    int t[numPipes][2];

    for (int i = 0; i < numPipes; i++)
    {
        pipe(t[i]);
    }
    

    


    for (i = 0; i < 3; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0){
            nietos[i] = fork();
            if(i==0 || i==2){
                if(nietos[i] == 0){
                    bisnieto1 = fork();
                }  
            }
            break;
        }
    }

    int buffer = 80;
    int n = (buffer)* sizeof(char);
    char *msg = NULL;
    msg = (char*) malloc(n);

    int flag;
    if(padre == getpid()){

        flag = 0;
        // Cerrar tuberias para el padre.
        for (int i = 0; i < numPipes; i++)
        {
            if(i!=13 && i!=0){
                close(t[i][0]);
                close(t[i][1]);
            }
        } 

        close(t[0][0]);
        close(t[13][1]);

        showtree();

        strcat(msg, letterToSend(flag));
        write(t[0][1], msg, n);
        read(t[13][0], msg, n);
        strcat(msg, letterToSend(flag));
        printf("%s \n", msg);
        close(t[0][1]);
        close(t[13][0]);

    }else{
        
        int lectura1 = -1, lectura2 = -1, escritura1 = -1, escritura2=-1;
        if(i==0){
            if(nietos[0]){
                //Padre b1.
                lectura1 = 8;
                escritura1 = 9; 
                lectura2 = 12;
                escritura2 = 13;
                flag = 6;
            }else{
                if(bisnieto1){
                    //Padre e
                    lectura1 = 9;
                    escritura1 = 10;
                    lectura2 = 11;
                    escritura2 = 12;
                    flag = 7;
                }else{
                    // Hijo h.
                    lectura1 = 10;
                    escritura1 = 11; 
                    flag = 8;
                }
            }
        }else if (i==1)
        {
            if(nietos[1]){
                //Padre c.
                lectura1 = 5;
                escritura1 = 6; 
                lectura2 = 7;
                escritura2 = 8;
                flag = 4;
            }else{
                //Hijo f.
                lectura1 = 6;
                escritura1 = 7; 
                flag = 5;
            }
        }else{
            if(nietos[2]){
                //Padre d.
               lectura1 = 0;
               escritura1 = 1;
               lectura2 = 4;
               escritura2 = 5;
               flag = 1;
            }else{
                if(bisnieto1){
                    //Padre g
                    lectura1 = 1;
                    escritura1 = 2;
                    lectura2 = 3;
                    escritura2 = 4;
                    flag = 2;
                }else{
                    // Hijo i.
                    lectura1 = 2;
                    escritura1 = 3;
                    flag = 3;
                }
            }


            for (int i = 0; i < numPipes; i++)
            {
                if(lectura2 == -1 && escritura2 == -1){
                    if(i!=lectura1 && i!=escritura1){
                        close(t[i][0]);
                        close(t[i][1]);
                    }
                }else{
                    if(i!=lectura1 && i!=escritura1 && i!=lectura2 && i!=escritura2){
                        close(t[i][0]);
                        close(t[i][1]);
                    }
                }
            }
            
           
        }

            close(t[lectura1][1]);
            close(t[escritura1][0]);

            if(lectura2 !=-1 && escritura2!=-1){
                close(t[lectura2][1]);
                close(t[escritura2][0]);
            }
            read(t[lectura1][0], msg, n);
            strcat(msg, letterToSend(flag));
            write(t[escritura1][1], msg, n);
            if(lectura2!=-1 && escritura2!=-1){
                read(t[lectura2][0], msg, n);
                strcat(msg, letterToSend(flag));
                write(t[escritura2][1], msg, n);
            }

            if(lectura2!=-1 && escritura2!=-1){
                close(t[lectura2][0]);
                close(t[escritura2][1]);
            }

    }

    return 0;
}
