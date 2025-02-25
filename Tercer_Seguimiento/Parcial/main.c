#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

void showtree() {
    char cmd[40] = {""};
    sprintf(cmd, "pstree -cAlp %d", getpid());
    system(cmd);
}


int main(int argc, char *argv[]){

    FILE *archivo_datos = NULL;
    archivo_datos = fopen(argv[1], "r");
    if(archivo_datos == NULL){
        printf("No se pudo abrir archivo %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    int N, M;
    fscanf(archivo_datos, "%d \n %d", &N, &M);

    printf("%d %d \n", N, M);

    //                                                                                                      MATRIZ DE NIVELES
    int filasNiveles = N;
    int columnasNiveles = M;
    int **matriz_nives = NULL;
    int id_matriz_nives = shmget(IPC_PRIVATE, (filasNiveles * sizeof(int *)), IPC_CREAT | S_IRUSR | S_IWUSR);
    matriz_nives = (int **) shmat(id_matriz_nives, 0, 0);
    if(matriz_nives == NULL){
        printf("No se pudo reservar espacio para matriz_nives\n");
        exit(EXIT_FAILURE);
    }
    
    int *ids_columnas_m_nives = NULL;
    int id_ids_columnas_m_nives = shmget(IPC_PRIVATE, filasNiveles * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    ids_columnas_m_nives = shmat(id_ids_columnas_m_nives, 0, 0);
    if(ids_columnas_m_nives == NULL){
        printf("No se pudo reservar espacio para ids_columnas_m_nives\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < filasNiveles; i++){
        ids_columnas_m_nives[i] = shmget(IPC_PRIVATE, (columnasNiveles * sizeof(int)), IPC_CREAT | S_IRUSR | S_IWUSR);
        matriz_nives[i] = (int *) shmat(ids_columnas_m_nives[i], 0, 0);
    }

    printf("MATRIZ NIVELES\n");
    for (int pi = 0; pi < filasNiveles; pi++){
        for (int pj = 0; pj < columnasNiveles; pj++){
            fscanf(archivo_datos, "%d", &matriz_nives[pi][pj]);
            printf("[%d] ", matriz_nives[pi][pj]);
        }
        printf("\n");
    }
    


    //                                                                                  MATRIZ DE CALIDAD
    int filasCalidad = N;
    int columnasCalidad = M;
    int **matriz_calidad = NULL;
    int id_matriz_calidad = shmget(IPC_PRIVATE, (filasCalidad * sizeof(int *)), IPC_CREAT | S_IRUSR | S_IWUSR);
    matriz_calidad = (int **) shmat(id_matriz_calidad, 0, 0);
    if(matriz_calidad == NULL){
        printf("No se pudo reservar espacio para matriz_calidad\n");
        exit(EXIT_FAILURE);
    }
    
    int *ids_columnas_m_calidad = NULL;
    int id_ids_columnas_m_calidad = shmget(IPC_PRIVATE, filasCalidad * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    ids_columnas_m_calidad = shmat(id_ids_columnas_m_calidad, 0, 0);
    if(ids_columnas_m_calidad == NULL){
        printf("No se pudo reservar espacio para ids_columnas_m_calidad\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < filasCalidad; i++){
        ids_columnas_m_calidad[i] = shmget(IPC_PRIVATE, (columnasCalidad * sizeof(int)), IPC_CREAT | S_IRUSR | S_IWUSR);
        matriz_calidad[i] = (int *) shmat(ids_columnas_m_calidad[i], 0, 0);
    }
    
    printf("MATRIZ CALIDAD\n");
    for (int pi = 0; pi < filasCalidad; pi++){
        for (int pj = 0; pj < columnasCalidad; pj++){
            fscanf(archivo_datos, "%d", &matriz_calidad[pi][pj]);
            printf("[%d] ", matriz_calidad[pi][pj]);
        }
        printf("\n");
    }
    

    //                                                                                  MATRIZ DE PREDICCION
    int filasPrediccion = N;
    int columnasPrediccion = M;
    int **matriz_prediccion = NULL;
    int id_matriz_prediccion = shmget(IPC_PRIVATE, (filasPrediccion * sizeof(int *)), IPC_CREAT | S_IRUSR | S_IWUSR);
    matriz_prediccion = (int **) shmat(id_matriz_prediccion, 0, 0);
    if(matriz_prediccion == NULL){
        printf("No se pudo reservar espacio para matriz_prediccion\n");
        exit(EXIT_FAILURE);
    }
    
    int *ids_columnas_m_prediccion = NULL;
    int id_ids_columnas_m_prediccion = shmget(IPC_PRIVATE, filasPrediccion * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    ids_columnas_m_prediccion = shmat(id_ids_columnas_m_prediccion, 0, 0);
    if(ids_columnas_m_prediccion == NULL){
        printf("No se pudo reservar espacio para ids_columnas_m_prediccion\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < filasPrediccion; i++){
        ids_columnas_m_prediccion[i] = shmget(IPC_PRIVATE, (columnasPrediccion * sizeof(int)), IPC_CREAT | S_IRUSR | S_IWUSR);
        matriz_prediccion[i] = (int *) shmat(ids_columnas_m_prediccion[i], 0, 0);
    }
    
    printf("MATRIZ PREDICCION\n");
    for (int pi = 0; pi < filasPrediccion; pi++){
        for (int pj = 0; pj < columnasPrediccion; pj++){
            fscanf(archivo_datos, "%d", &matriz_prediccion[pi][pj]);
            printf("[%d] ", matriz_prediccion[pi][pj]);
        }
        printf("\n");
    }

    //                                                                                          MATRIZ DE RIESGO
    
    int filasRiesgo = N;
    int columnasRiesgo = M;
    double **matriz_riesgo = NULL;
    int id_matriz_riesgo = shmget(IPC_PRIVATE, (filasRiesgo * sizeof(double *)), IPC_CREAT | S_IRUSR | S_IWUSR);
    matriz_riesgo = (double **) shmat(id_matriz_riesgo, 0, 0);
    if(matriz_riesgo == NULL){
        printf("No se pudo reservar espacio para matriz_riesgo\n");
        exit(EXIT_FAILURE);
    }
    
    int *ids_columnas_m_riesgo = NULL;
    int id_ids_columnas_m_riesgo = shmget(IPC_PRIVATE, filasRiesgo * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    ids_columnas_m_riesgo = shmat(id_ids_columnas_m_riesgo, 0, 0);
    if(ids_columnas_m_riesgo == NULL){
        printf("No se pudo reservar espacio para ids_columnas_m_riesgo\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < filasRiesgo; i++){
        ids_columnas_m_riesgo[i] = shmget(IPC_PRIVATE, (columnasRiesgo * sizeof(double)), IPC_CREAT | S_IRUSR | S_IWUSR);
        matriz_riesgo[i] = (double *) shmat(ids_columnas_m_riesgo[i], 0, 0);
    }


    //                                                                      MATRIZ DE SOSTENIBILIDAD
    int filasSostenibilidad = N;
    int columnasSostenibilidad = M;
    double **matriz_sostenibilidad = NULL;
    int id_matriz_sostenibilidad = shmget(IPC_PRIVATE, (filasSostenibilidad * sizeof(double *)), IPC_CREAT | S_IRUSR | S_IWUSR);
    matriz_sostenibilidad = (double **) shmat(id_matriz_sostenibilidad, 0, 0);
    if(matriz_sostenibilidad == NULL){
        printf("No se pudo reservar espacio para matriz_sostenibilidad\n");
        exit(EXIT_FAILURE);
    }
    
    int *ids_columnas_m_sostenibilidad = NULL;
    int id_ids_columnas_m_sostenibilidad = shmget(IPC_PRIVATE, filasSostenibilidad * sizeof(int), IPC_CREAT | S_IRUSR | S_IWUSR);
    ids_columnas_m_sostenibilidad = shmat(id_ids_columnas_m_sostenibilidad, 0, 0);
    if(ids_columnas_m_sostenibilidad == NULL){
        printf("No se pudo reservar espacio para ids_columnas_m_sostenibilidad\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < filasSostenibilidad; i++){
        ids_columnas_m_sostenibilidad[i] = shmget(IPC_PRIVATE, (columnasSostenibilidad * sizeof(double)), IPC_CREAT | S_IRUSR | S_IWUSR);
        matriz_sostenibilidad[i] = (double *) shmat(ids_columnas_m_sostenibilidad[i], 0, 0);
    }

    //                                                                                                          LOGICA DE ALERTA
    int nProcesos = 2;
    int nAlertas = atoi(argv[2]);
    int *vector_alerta = NULL;
    int tam_vector_alerta = nProcesos;
    int id_vector_alerta = shmget(IPC_PRIVATE, (tam_vector_alerta * sizeof(int)), IPC_CREAT | S_IRUSR | S_IWUSR);
    vector_alerta = (int *) shmat(id_vector_alerta, 0, 0);
    if(vector_alerta == NULL){
        printf("No se pudo reservar espacio para vector_alerta\n");
        exit(EXIT_FAILURE);
    }
    printf("VECTOR DE ALERTAS\n");
    for (int pi = 0; pi < tam_vector_alerta; pi++){
        vector_alerta[pi] = 0;
        printf("[%d] ", vector_alerta[pi]);
    }
    printf("\n");
    




    //                                                                                                              CREACION DE LOS PROCESOS HIJOS

    pid_t *pidProcesos = NULL;
    pidProcesos = (pid_t *)malloc(nProcesos * sizeof(pid_t));
    if(pidProcesos == NULL){
        printf("No se pudo reservar memoria para pidProcesos\n");
        exit(EXIT_FAILURE);
    }
    int idxHijos;
    for (idxHijos = 0; idxHijos < nProcesos; idxHijos++){
        pidProcesos[idxHijos] = fork();
        if (pidProcesos[idxHijos] == 0){
            break;
        }
    }


    if(idxHijos == nProcesos){                                                      ///PADRE ANALISTA DE ALERTA
        int status;
        for(int i=0; i < nProcesos; i++){
            waitpid(pidProcesos[i], &status, 0);
        }

        int **matriz_d_alerta = NULL;
        int filas_m_d_alerta = N;
        int columnas_m_d_alerta = M;
        matriz_d_alerta = (int **) malloc(filas_m_d_alerta * sizeof(int *));
        if(matriz_d_alerta == NULL){
            printf("No se pudo reservar espacio para matriz_d_alerta\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < filas_m_d_alerta; i++){
            matriz_d_alerta[i] = (int *) malloc(columnas_m_d_alerta * sizeof(int));
        }
        printf("MATRIZ DE ALERTA\n");
        for (int pi = 0; pi < filas_m_d_alerta; pi++){
            for (int pj = 0; pj < columnas_m_d_alerta; pj++){
                if(matriz_riesgo[pi][pj] > 1.5 && matriz_sostenibilidad[pi][pj] < 0.3){
                    matriz_d_alerta[pi][pj] = 2;
                }else if(matriz_riesgo[pi][pj] > 1.2 && matriz_sostenibilidad[pi][pj] < 0.4){
                    matriz_d_alerta[pi][pj] = 1;
                }else{
                    matriz_d_alerta[pi][pj] = 0;
                }
            }
        }
        
        for (int pi = 0; pi < filas_m_d_alerta; pi++){
            for (int pj = 0; pj < columnas_m_d_alerta; pj++){
                printf("[%d] ", matriz_d_alerta[pi][pj]);
            }
            printf("\n");
        }

        //LIBERAR ESPACIO DE LA matriz_d_alerta
        for(int i = 0; i < filas_m_d_alerta; i++){
            free(matriz_d_alerta[i]);
            matriz_d_alerta[i] = NULL;
        }
        free(matriz_d_alerta);
        matriz_d_alerta = NULL;

        //DESCONECTARSE Y ELIMINAR vector_alerta
        shmdt(vector_alerta);
        shmctl(id_vector_alerta, IPC_RMID, 0);
        vector_alerta = NULL;

        //DESCONECTARSE Y ELIMINAR matriz_sostenibilidad
        for (int i = 0; i < filasSostenibilidad; i++){
            shmdt(matriz_sostenibilidad[i]);
            shmctl(ids_columnas_m_sostenibilidad[i], IPC_RMID, 0);
        }
        shmdt(matriz_sostenibilidad);
        shmctl(id_matriz_sostenibilidad, IPC_RMID, 0);
        matriz_sostenibilidad = NULL;
        shmdt(ids_columnas_m_sostenibilidad);
        shmctl(id_ids_columnas_m_sostenibilidad, IPC_RMID, 0);
        ids_columnas_m_sostenibilidad = NULL;
        


    //DESCONECTARSE Y ELIMINAR matriz_riesgo
        for (int i = 0; i < filasRiesgo; i++){
            shmdt(matriz_riesgo[i]);
            shmctl(ids_columnas_m_riesgo[i], IPC_RMID, 0);
        }
        shmdt(matriz_riesgo);
        shmctl(id_matriz_riesgo, IPC_RMID, 0);
        matriz_riesgo = NULL;
        shmdt(ids_columnas_m_riesgo);
        shmctl(id_ids_columnas_m_riesgo, IPC_RMID, 0);
        ids_columnas_m_riesgo = NULL;
        

        //DESCONECTARSE Y ELIMINAR matriz_prediccion
        for (int i = 0; i < filasPrediccion; i++){
            shmdt(matriz_prediccion[i]);
            shmctl(ids_columnas_m_prediccion[i], IPC_RMID, 0);
        }
        shmdt(matriz_prediccion);
        shmctl(id_matriz_prediccion, IPC_RMID, 0);
        matriz_prediccion = NULL;
        shmdt(ids_columnas_m_prediccion);
        shmctl(id_ids_columnas_m_prediccion, IPC_RMID, 0);
        ids_columnas_m_prediccion = NULL;
        
        //DESCONECTARSE Y ELIMINAR matriz_calidad
        for (int i = 0; i < filasCalidad; i++){
            shmdt(matriz_calidad[i]);
            shmctl(ids_columnas_m_calidad[i], IPC_RMID, 0);
        }
        shmdt(matriz_calidad);
        shmctl(id_matriz_calidad, IPC_RMID, 0);
        matriz_calidad = NULL;
        shmdt(ids_columnas_m_calidad);
        shmctl(id_ids_columnas_m_calidad, IPC_RMID, 0);
        ids_columnas_m_calidad = NULL;
        
        //DESCONECTARSE Y ELIMINAR matriz_nives
        for (int i = 0; i < filasNiveles; i++){
            shmdt(matriz_nives[i]);
            shmctl(ids_columnas_m_nives[i], IPC_RMID, 0);
        }
        shmdt(matriz_nives);
        shmctl(id_matriz_nives, IPC_RMID, 0);
        matriz_nives = NULL;
        shmdt(ids_columnas_m_nives);
        shmctl(id_ids_columnas_m_nives, IPC_RMID, 0);
        ids_columnas_m_nives = NULL; 
        
    }else{


            if(idxHijos == 0){                                                      ///HIJO 1 ANALISTA DE RIESGO
                printf("HIJO ANALISTA DE RIESGO\n");
                for (int pi = 0; pi < filasRiesgo; pi++){
                    for (int pj = 0; pj < columnasRiesgo; pj++){
                        matriz_riesgo[pi][pj] = (double) (1 * (100-matriz_nives[pi][pj]) * (2 - matriz_calidad[pi][pj]) * (1 - matriz_prediccion[pi][pj]))/100;
                    }
                }
                for (int pi = 0; pi < filasRiesgo; pi++){
                    for (int pj = 0; pj < columnasRiesgo; pj++){
                        printf("[%.2lf] ", matriz_riesgo[pi][pj]);
                    }
                    printf("\n");
                }
            }else{ 
                                                                            ///HIJO 2 ANALISTA DE SOSTENIBILIDAD

            sleep(1);
                printf("HIJO ANALISTA DE SOSTENIBILIDAD\n");
                for (int pi = 0; pi < filasSostenibilidad; pi++){
                    for (int pj = 0; pj < columnasSostenibilidad; pj++){
                        matriz_sostenibilidad[pi][pj] = (double) (2 * (matriz_nives[pi][pj]) * (matriz_calidad[pi][pj] + 1) * (matriz_prediccion[pi][pj] + 2))/100;
                    }
                }

                for (int pi = 0; pi < filasSostenibilidad; pi++){
                    for (int pj = 0; pj < columnasSostenibilidad; pj++){
                        printf("[%.2lf] ", matriz_sostenibilidad[pi][pj]);
                    }
                    printf("\n");
                }
            }
            vector_alerta[idxHijos] = 1;

        
        
    


        //DESCONECTARSE Y ELIMINAR vector_alerta
        shmdt(vector_alerta);
        shmctl(id_vector_alerta, IPC_RMID, 0);
        vector_alerta = NULL;

        //DESCONECTARSE Y ELIMINAR matriz_sostenibilidad
        for (int i = 0; i < filasSostenibilidad; i++){
            shmdt(matriz_sostenibilidad[i]);
        }
        shmdt(matriz_sostenibilidad);
        matriz_sostenibilidad = NULL;
        shmdt(ids_columnas_m_sostenibilidad);
        ids_columnas_m_sostenibilidad = NULL;
        
        //DESCONECTARSE Y ELIMINAR matriz_riesgo
        for (int i = 0; i < filasRiesgo; i++){
            shmdt(matriz_riesgo[i]);
        }
        shmdt(matriz_riesgo);
        matriz_riesgo = NULL;
        shmdt(ids_columnas_m_riesgo);
        ids_columnas_m_riesgo = NULL;
        

        //DESCONECTARSE Y ELIMINAR matriz_prediccion
        for (int i = 0; i < filasPrediccion; i++){
            shmdt(matriz_prediccion[i]);
        }
        shmdt(matriz_prediccion);
        matriz_prediccion = NULL;
        shmdt(ids_columnas_m_prediccion);
        ids_columnas_m_prediccion = NULL;
        
        //DESCONECTARSE Y ELIMINAR matriz_calidad
        for (int i = 0; i < filasCalidad; i++){
            shmdt(matriz_calidad[i]);
        }
        shmdt(matriz_calidad);
        matriz_calidad = NULL;
        shmdt(ids_columnas_m_calidad);
        ids_columnas_m_calidad = NULL;
        
        //DESCONECTARSE Y ELIMINAR matriz_nives
        for (int i = 0; i < filasNiveles; i++){
            shmdt(matriz_nives[i]);
        }
        shmdt(matriz_nives);
        matriz_nives = NULL;
        shmdt(ids_columnas_m_nives);
        ids_columnas_m_nives = NULL;
    }

    
    //ELIMINAR ESPACIO DE MEMORIA PARA pidProcesos
    free(pidProcesos);
    pidProcesos = NULL;

    //CERRAR ARCHIVO archivo_datos
    fclose(archivo_datos);
    archivo_datos = NULL;

}