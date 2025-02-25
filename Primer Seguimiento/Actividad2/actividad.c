#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


long int leerTotal(FILE *f){
    long int suma1, suma2;

    if(!f){printf("Cant open file"); return -1;}

    fscanf(f, "%ld", &suma1);
    fscanf(f, "%ld", &suma2);

    return suma1+suma2;
}


int main(int argc, char const *argv[])
{
    
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

    // Create the file to write.

    FILE *fw;

    fw = fopen("out.txt", "w");


    // Read content in  file and pass to array.

    for (int i = 0; i < size; i++)
    {
        fscanf(f, "%d", &array[i]);
    }
    

    // Process creation

    pid_t childs[2], fatherP=getpid();

    for (int i = 0; i < 2; i++)
    {
       childs[i] = fork();
       if(childs[i]==0){
        if(i==0){
            long int sum = 0;
            for (int j = 0; j < size/2; j++)
            {
                sum += array[j];
            }
            fprintf(fw, "%ld ", sum);
            
        }else{
            long int sum = 0;
            for (int k = size/2; k < size; k++)
            {
                sum += array[k];
               
            }
            fprintf(fw, "%ld ", sum);
        }
        break;
       } 
    }
    

    // Wait for child process to end

    if(fatherP == getpid()){
        for (int i = 0; i < 2; i++)
        {
            wait(NULL);
        }

        FILE *fs;
        fs = fopen("out.txt", "r");
        long int s = leerTotal(fs);
        printf("%ld \n", s);
        
    }

    
    fclose(f);
    return EXIT_SUCCESS;
}
