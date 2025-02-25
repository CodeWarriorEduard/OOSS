#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<sys/types.h>

#define BUFFER_SIZE 1024

void showtree(){
    char b[500];
    sprintf(b, "pstree -lp %d", getpid());
    system(b);
}

int main(int argc, char const *argv[])
{
    // Declaracion de buffer.
    char BufferIn[BUFFER_SIZE];
    char BufferOut[BUFFER_SIZE];
    int n;
    printf("Ingrese el numero de hijos > ");
    scanf("%d", &n);
    getchar(); // Consumir salto de linea.
    // Creacion de array para almacenar hijos

    pid_t hijos[n], padre = getpid();
    // hijos = (int *) malloc(n * sizeof(int));

    printf("Tamano hijos %d", sizeof(hijos)/sizeof(hijos[0]));
   
    // Validar locacion de memoria.

    if(hijos == NULL){
        perror("Error asignando memoria");
        exit(1);
    }
    
    // Los pipes deben crearse antes del fork();
    // Number of pipes n * 2
    // Creacion de tuberias.

    int numPipes = n; // Numero de tuberias

    int t[numPipes][2]; // Mala practica, funciona, ver como mejorar.
    int t2[numPipes][2];

    for (int i = 0; i < numPipes; i++)
    {
        pipe(t[i]);
        pipe(t2[i]);        
    }
    
    // Recordar que c no es null safe
    // Creacion de hijos

    int idxHijos;
    printf("Creando %d hijos \n", n);
    for (idxHijos = 0; idxHijos < n; idxHijos++)
    {     
        if((hijos[idxHijos] = fork()) > 0) break;
    }

    // Mostrar arbol de procesos.
    if(padre == getpid()){
        showtree();
    }else{
        sleep(1);
    }

    if(idxHijos == 0){ // Padre.

        for (int i = 1; i < n; i++)
        {
            close(t[i][0]);
            close(t2[i][0]);
            close(t[i][1]);
            close(t2[i][1]);
        }    

        close(t[0][1]);
        close(t2[0][0]);  

        fflush(stdin);
        printf("\nIngrese el mensaje >");
        fgets(BufferIn, sizeof(BufferIn), stdin);

        // Top to down

        if(strlen(BufferIn)>0){
            printf("Process %d mensaje %s \n", getpid(), BufferIn);
            write(t2[0][1], BufferIn, strlen(BufferIn) + 1);
        }

        wait(NULL);
        // Down to top
        int n = read(t[0][0], BufferOut, BUFFER_SIZE);
        printf("n: %d", n);
        if(n>0){
            printf("Process %d mensaje %s \n", getpid(), BufferOut);
            BufferOut[n] = '\0';
            printf("Mensaje %s \n", BufferOut);
        }
        
        for (int i = 0; i < n; i++)
        {
            wait(NULL);
        }
        

    }else if (idxHijos == n) // Ultimo hijo
    {
        for (int i = n-2; i >=0; i--)
        {
            close(t[i][0]);
            close(t2[i][0]);
            close(t[i][1]);
            close(t2[i][1]);
        }

        close(t[idxHijos][1]);
        close(t2[idxHijos][0]);  

        // Top to down
        int n = read(t2[idxHijos-1][0], BufferOut, BUFFER_SIZE);

        if(n>0){
            BufferOut[n] = '\0';
            printf("Process %d mensaje %s \n", getpid(), BufferOut);
            write(t[idxHijos-1][1], BufferOut, sizeof(BufferOut));
        }

        // // Down to top
        write(t[idxHijos-1][1], BufferOut, sizeof(BufferOut));

        
    }else{
        close(t[idxHijos-1][0]);
        close(t2[idxHijos-1][1]);
        close(t[idxHijos][1]);
        close(t2[idxHijos][0]);

        // Enviar el mensaje mediante las tuberias top to down.
        int n = read(t2[idxHijos-1][0], BufferOut, BUFFER_SIZE);
        if(n>0){
            BufferOut[n] = '\0';
            printf("Process %d mensaje %s \n", getpid(), BufferOut);
            write(t2[idxHijos][1], BufferOut,sizeof(BufferOut));
            int j = read(t[idxHijos][0], BufferOut, BUFFER_SIZE); 
            if(j>0){
                    BufferOut[n] = '\0';
                    printf("Process %d mensaje %s \n", getpid(), BufferOut);
                    write(t[idxHijos-1][1], BufferOut,sizeof(BufferOut));
            }

            
        }        

    }
    



    return 0;
}
