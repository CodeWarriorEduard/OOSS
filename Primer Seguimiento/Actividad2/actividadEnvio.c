#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


long int leerTotal(char *f, int limiteSuperior){

    FILE *fs;
    fs = fopen(f, "r");

    long int sumaTotal = 0;
    long int value;

    if(!f){printf("Cant open file"); return -1;}

    for (int i = 0; i < limiteSuperior; i++)
    {
        fscanf(fs, "%ld", &value);
        sumaTotal+=value;
    }
    
   
    return sumaTotal;
}


int main(int argc, char const *argv[])
{
    remove("out.txt");
    FILE *f;
    f = fopen(argv[1], "r");


    if(f == NULL){
        printf("Cant open file");
        exit(EXIT_FAILURE);
    }

    // Size of data input

    int size;
    int *array = NULL;
    fscanf(f, "%d", &size);
    array = (int*)malloc(size * sizeof(int));

    
    // Read content in  file and pass to array.

    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%d", &array[i]);
    }
    

    // Creacion de procesos.

    int nP; // Numero de procesos
    printf("Insert the number of process: ");
    scanf("%d", &nP);

    if(nP>size){
        printf("Error el numero de procesos no puede exceder el tamaño del arreglo \n");
        exit(EXIT_FAILURE);
    }

    pid_t childs[nP], fatherP=getpid();

    // Crear el archivo en el que se va a escribir.
    FILE *fw;
    fw = fopen("out.txt", "w");

    int sP = size/nP; // sP es la cantidad de enteros a sumar en cada proceso.


    for (int i = 0; i < nP; i++)
    {
       childs[i] = fork();
       if(childs[i]==0){

        int limiteInferior = i * sP;
        int limiteSuperior = (i+1)*sP;
        long int sum = 0;

        
        if(i == (nP - 1)){
            limiteSuperior += (size%nP);
        }

        for (int j = limiteInferior; j < limiteSuperior; j++)
        {
            sum+=array[j];
        }
        printf("Child [%d] Sum: %ld \n", getpid(), sum);
        fprintf(fw, "%ld ", sum);
          
        break;
       } 
    }
    

    // Esperar a que los hijos terminen.

    if(fatherP == getpid()){
        for (int i = 0; i < nP; i++)
        {
            wait(NULL);
        }

        // Lectura de archivo para calcular total.
        char *f = "out.txt";
        long int s = leerTotal(f, nP);
        printf("%ld \n", s);
        
    }

    free(array);
    fclose(f);

    return EXIT_SUCCESS;
}
