#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 50

void showtree()
{
    char b[500];
    sprintf(b, "pstree -lp %d", getpid());
    system(b);
}

char *imprePos(int quien)
{
    char *text;
    if (quien == 1)
    {
        text = "a-";
    }
    if (quien == 2)
    {
        text = "d-";
    }
    if (quien == 3)
    {
        text = "c-";
    }
    if (quien == 4)
    {
        text = "e-";
    }
    if (quien == 5)
    {
        text = "f-";
    }
    if (quien == 6)
    {
        text = "h-";
    }
    if (quien == 7)
    {
        text = "g-";
    }
    if (quien == 8)
    {
        text = "b-";
    }
    return text;
}

int main(int argc, char const *argv[])
{
    pid_t child[3], nieto, bisnieto, hijosBis[2], padre = getpid();
    int idxHijos;

    int numPipes = 11;

    int t[numPipes][2];

    // Creacion de tuberias
    for (int i = 0; i < numPipes; i++)
    {
        pipe(t[i]);
    }
    // Variable global.
    int numIter;
    printf("Digite numero de iteraciones: ");
    scanf("%d", &numIter);
    // Creacion de hijos
    for (idxHijos = 0; idxHijos < 3; idxHijos++)
    {
        if ((child[idxHijos] = fork()) == 0)
        {
            if (idxHijos == 1)
            {
                nieto = fork();
                if (nieto == 0)
                {
                    bisnieto = fork();
                    if (bisnieto == 0)
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            hijosBis[i] = fork();
                            if (hijosBis[i] == 0)
                                break;
                        }
                    }
                }
            }
            break;
        }
    }

    ssize_t a = (BUFFER_SIZE * numIter) * sizeof(char);
    char *msg = NULL;
    msg = (char *)malloc(a);
    int flag;

    if (padre == getpid())
    {
        for (int i = 0; i < numPipes; i++)
        {
            if (i != 0 && i != 10)
            {
                close(t[i][0]);
                close(t[i][1]);
            }
        }

        showtree();
        flag = 1;
        for (int i = 0; i < numIter; i++)
        {
            strcat(msg, imprePos(flag));
            write(t[0][1], msg, a);
            read(t[10][0], msg, a);
            strcat(msg, imprePos(flag));
            strcat(msg, " ");
        }
        close(t[10][0]);
        close(t[0][1]);
        printf("%s\n", msg);
    }
    else
    {
        int lectura1 = -1, escritura1 = -1, lectura2 = -1, escritura2 = -1;
        for (int i = 0; i < numIter; i++)
        {
            if (idxHijos == 1)
            {
                if (nieto == 0)
                {
                    if (bisnieto == 0)
                    {
                        if (hijosBis[0] != 0 && hijosBis[1] != 0)
                        {
                            // Si estoy en el padre, F.
                            lectura1 = 3;
                            escritura1 = 4;
                            lectura2 = 6;
                            escritura2 = 7;
                            flag = 5;
                        }
                        else
                        {
                            if (hijosBis[0] == 0)
                            {
                                // G
                                lectura1 = 5;
                                escritura1 = 6;
                                flag = 7;
                            }
                            else if (hijosBis[1] == 0)
                            {
                                // H
                                lectura1 = 4;
                                escritura1 = 5;
                                flag = 6;
                            }
                        }
                    }
                    else
                    {
                        // Padre del bisnieto, nieto, E.
                        lectura1 = 2;
                        escritura1 = 3;
                        lectura2 = 7;
                        escritura2 = 8;
                        flag = 4;
                    }
                }
                else
                {
                    // Padre del nieto., C.
                    lectura1 = 1;
                    escritura1 = 2;
                    lectura2 = 8;
                    escritura2 = 9;
                    flag = 3;
                }
            }
            else if (idxHijos == 0)
            {

                lectura1 = 9;
                escritura1 = 10;
                flag = 8;
            }
            else if (idxHijos == 2)
            {
                lectura1 = 0;
                escritura1 = 1;
                flag = 2;
            }

            for (int i = 0; i < numPipes; i++)
            {
                if (lectura2 == -1 && escritura2 == -1)
                {
                    if (i != lectura1 && i != escritura1)
                    {
                        close(t[i][0]);
                        close(t[i][1]);
                    }
                }
                else
                {
                    if (i != lectura1 && i != escritura1 && i != lectura2 && i != escritura2)
                    {
                        close(t[i][0]);
                        close(t[i][1]);
                    }
                }
            }

            close(t[lectura1][1]);
            close(t[escritura1][0]);
            if (lectura2 != -1 && escritura2 != -1)
            {
                close(t[lectura2][1]);
                close(t[escritura2][0]);
            }

            read(t[lectura1][0], msg, a);
            strcat(msg, imprePos(flag));
            write(t[escritura1][1], msg, a);
            if (lectura2 != -1 && escritura2 != -1)
            {
                read(t[lectura2][0], msg, a);
                strcat(msg, imprePos(flag));
                write(t[escritura2][1], msg, a);
            }
        }
            close(t[lectura1][0]);
            close(t[escritura1][1]);
            if (lectura2 != -1 && escritura2 != -1)
            {
              
                close(t[lectura2][0]);
                close(t[escritura2][1]);
            }
    }

    return 0;
}
