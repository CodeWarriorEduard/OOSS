#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h> // Flags.
#include<sys/wait.h>

#define BUFFER_SIZE 1024

void showTree(){
    char b[500];
    sprintf(b, "\n pstree -lp %d", getpid());
    system(b);
}


int main(int argc, char const *argv[])
{
    pid_t childs[2], root = getpid();
    int t1[2], t2[2];
    int i;

    // Declaramos el buffer

    char buffer[BUFFER_SIZE];

    
    ssize_t byte_read;


    pipe(t1);
    pipe(t2);

    for (i = 0; i < 2; i++)
    {
        childs[i] = fork();
        if(childs[i] == 0)break;
    }


    if(i==2){

        // PADRE.

        close(t1[1]);
        close(t2[0]);
        close(t2[1]);

        printf("Padre 1 \n");
        wait(NULL);
        wait(NULL);
    }else if (i == 1)
    {
        close(t1[0]);
        close(t2[1]);

        int c = 0;
        // Leer el archivo
        while ((byte_read = read(t2[0], buffer, sizeof(buffer) - 1) ) > 0)
        {
            buffer[byte_read] = '\0';
            for (int i = 0; i < byte_read; i++)
            {
                if(buffer[i] == 'a' || buffer[i] == 'e' || buffer[i] == 'i' || buffer[i] == 'o' || buffer[i] == 'u' || buffer[i] == 'A' || buffer[i] == 'E' || buffer[i] == 'I' || buffer[i] == 'O' || buffer[i] == 'U'){
                    c++;
                }
            }
            write(fileno(stdout), buffer, byte_read);
        }


        
        printf("\n El numero de vocales en el texto es: %d \n", c);
        


        close(t2[0]);
        exit(0);
    }else{
        close(t1[0]);
        close(t1[1]);
        close(t2[0]);

        // HIJO .

        // Escrir en la tuberia 2 para mandar al hijo 1.
        // 1. Leer archivo.

        
        int file = open(argv[1], O_RDONLY);

        if(file == -1){
            perror("Error opening file");
            exit(1);
        }

        // 2. Escribir en la tubería. 

        while ((byte_read = read(file, buffer, BUFFER_SIZE)) >0 )
        {
            write(t2[1], buffer, byte_read); // Estudiar la llamada al sistema write.
        }
        
        printf("Se terminó de escribir sobre la tubería \n");
       

    }
    


    if(root == getpid()){
        showTree();
        
    }else{
        sleep(1);
    }
    

    return 0;
}
