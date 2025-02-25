#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int hayMinas(int **m, int i, int j, int iF, int iC, int fF, int fC){

    int hayMina = 0;

    int inicioF = i - 1;
    int inicioC = j - 1;
    int finF = i + 1;
    int finC = j + 1;

    // Validar si el cuadrante es nXn
    
    // Recorrer diagonal principal

   for (int k = inicioF; k <= finF; k++){
        for (int l = inicioC; l <= finC; l++){
            if (k >= iF && k <= fF){
                if (l >= iC && l <= fC){
                    if (m[k][l] == 2){
                        hayMina =  1;
                        break;
                    }
                    
                }
                
            }
            
        }
    }

    return hayMina;

    
    

}





int main(int argc, char const *argv[]){

    int mitadC, mitadF;

    FILE * f;

    f = fopen(argv[1], "r");

    int filas, columnas;


    fscanf(f, "%d \n %d",&filas, &columnas);

    // Validacion de tamaño
    if(filas <1 && columnas<1){
       perror("No es una matriz valida");
       exit(1);
    }
    // Dividimos en cuadrantes.
    mitadF = filas/2;
    mitadC = columnas/2;

    int **m = NULL;

    // Asignar memoria a la matriz

    m = (int**) malloc(filas * sizeof(int*));

    if(m==NULL){
        perror("Error asignando memoria a matriz");
        exit(1);
    }

    for (int i = 0; i < filas; i++)
    {
        m[i] = (int*) malloc(columnas *sizeof(int));
        if(m[i]== NULL){
            perror("Error asignando memoria a matriz");
            exit(1);
        }
    }


    // Guardar los datos del texto en la matriz.

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            fscanf(f, "%d", &m[i][j]);
        }
        
    }

     for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            printf("[%d]", m[i][j]);
        }
        printf("\n");
    }
    

    // Creacion de hijos

        pid_t hijos[4], root = getpid();
        int idxI;

        // Creacion de tuberias
        int t1[2], t2[2];

        pipe(t1);
        pipe(t2);

        for ( idxI = 0; idxI < 4; idxI++)
        {
            hijos[idxI] = fork();
            if(hijos[idxI] == 0) break;
        }
        

        if(root == getpid()){ // Padre
            close(t1[1]);
            close(t2[1]);

            int vR[2];
            int status;

            int cantidad = 0;

            

            for (int i = 0; i < 4; i++)
            {
                waitpid(hijos[i], &status, 0);
                read(t2[0], &cantidad, sizeof(int));
                for (int j = 0; j < cantidad; j++)
                {
                    read(t1[0], vR, sizeof(int[2]));
                    printf("\n pos mina encontrada x: %d y: %d \n", vR[0], vR[1]);
                }
                
           
            }
            
            
            close(t1[0]);
            close(t2[0]);

        }else{
            close(t2[0]);
            close(t1[0]);
            int c = 0;
            if(idxI == 0){
                

                int inicioF = 0;
                int finF = mitadF;
                int inicioC = 0;
                int finCol = mitadC;

                for (int i = inicioF; i < finF; i++)
                {
                    for (int j = inicioC; j < finCol; j++)
                    {
                       if(m[i][j] == 1){
                        int b = hayMinas(m,i,j,inicioF, inicioC, finF, finCol);

                        if(b == 1){
                            c++;
                            int v[2];
                            v[0] = i;
                            v[1] = j;
                            write(t1[1], v, sizeof(int[2]));    
                        }
                  
                       }
                    }
                    
                }






                
                


            }else if (idxI==1){



                int inicioF = 0;
                int finF = mitadF;
                int inicioC = mitadC;
                int finCol = columnas;

                for (int i = inicioF; i < finF; i++)
                {
                    for (int j = inicioC; j < finCol; j++)
                    {
                       if(m[i][j] == 1){
                        int b = hayMinas(m,i,j,inicioF, inicioC, finF, finCol);

                        if(b == 1){
                            c++;
                            int v[2];
                            v[0] = i;
                            v[1] = j;
                            write(t1[1], v, sizeof(int[2]));    
                        }
                  
                       }
                    }
                    
                }
                
                
            }else if (idxI == 2)
            {



                 int inicioF = mitadF;
                int finF = filas;
                int inicioC = 0;
                int finCol = mitadC;

                for (int i = inicioF; i < finF; i++)
                {
                    for (int j = inicioC; j < finCol; j++)
                    {
                       if(m[i][j] == 1){
                        int b = hayMinas(m,i,j,inicioF, inicioC, finF, finCol);

                        if(b == 1){
                            c++;
                            int v[2];
                            v[0] = i;
                            v[1] = j;
                            write(t1[1], v, sizeof(int[2]));    
                        }
                  
                       }
                    }
                    
                }

                
               
            }else{


 
                 int inicioF = mitadF;
                int finF = filas;
                int inicioC = mitadC;
                int finCol = columnas;

               for (int i = inicioF; i < finF; i++)
                {
                    for (int j = inicioC; j < finCol; j++)
                    {
                       if(m[i][j] == 1){
                        int b = hayMinas(m,i,j,inicioF, inicioC, finF, finCol);

                        if(b == 1){
                            c++;
                            int v[2];
                            v[0] = i;
                            v[1] = j;
                            write(t1[1], v, sizeof(int[2]));    
                        }
                  
                       }
                    }
                    
                }
                

            }
            write(t2[1], &c, sizeof(int));
            close(t2[1]);
            close(t1[1]); 
            
        }



    // Liberacion de memoria
    for (int i = 0; i < filas; i++)
    {
        free(m[i]);
        m[i] = NULL;
    }
    
    free(m);
    m = NULL;









    

    return EXIT_SUCCESS;
}


