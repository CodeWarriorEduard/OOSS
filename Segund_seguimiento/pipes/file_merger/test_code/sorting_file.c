#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[])
{
    FILE *f;

    f = fopen(argv[1], "r");

    int size;

    fscanf(f, "%d", &size);
    printf("%d \n", size);

    char **file1;


    file1 = (char**)malloc((size) * sizeof(char*));

    for (int i = 0; i < size; i++)
    {
        file1[i] = malloc(size);
        if(!file1[i] || !fgets(file1[i], size, f)){
            free(file1[i]);
            file1[i] = NULL;
            break;
        }

        file1[i][strcspn(file1[i], "\n")] = '\0';
    }

    printf("Printing file: \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d", i);
        printf("%s \n", file1[i]);
    }

    fclose(f);
    return 0;
}
