#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<sys/types.h>

typedef struct reporteAparicion
{
    int A;
    int T;
    int C;
    int G;
    pid_t pid;
}reporteAparicion;


typedef struct reporteBase
{
    int pos;
    pid_t pid;
}reporteBase;



int main(int argc, char const *argv[])
{
    FILE *f = NULL;

    f = fopen(argv[1], "r");

    if(f == NULL){
        perror("Error reading file \n");
        exit(1);
    }


    // Leer numero de bases en total

    int nBases;

    char *lineaBase = NULL;

    fscanf(f, "%d", &nBases);

    // Memoria compartida
    int idLineaBase = shmget(IPC_PRIVATE, nBases*sizeof(char), IPC_CREAT|S_IRUSR|S_IWUSR);

    lineaBase = (char*) shmat(idLineaBase, 0,0);

    char c;
    int count = 0;
    while ((c=getc(f))!=EOF)
    {
        if(c!='\n'){
            lineaBase[count++] = c;
        }

    }
    


    // Creacion de hijos.

    int nHijos = atoi(argv[2]);
    pid_t *hijos, padre = getpid();

    hijos = (pid_t*) malloc(nHijos*sizeof(pid_t));
    int idxHijos;
    // Calculo de sectores del vector para cada proceso.

    int particion = (int) (nBases/(nHijos-1));

    int restante = nBases - (particion*(nHijos-1));


    for (idxHijos = 0; idxHijos < nHijos; idxHijos++)
    {
            if((hijos[idxHijos] = fork())==0) break;
    }
    


    if(padre == getpid()){



    }else{
        sleep(1);
        if(idxHijos == (nHijos - 1)){

        }else{
            int inicio = idxHijos * particion;
            int final = (idxHijos + 1)*particion;
            if(idxHijos == (nHijos - 2)){
                final += restante;
            }
            for (int i = inicio; i < final; i++)
            {
                /* code */
            }
            
        }
    }
    
    



    return 0;
}
