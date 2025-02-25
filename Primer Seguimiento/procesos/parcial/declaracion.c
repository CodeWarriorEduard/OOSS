#include<stdio.h>

int (*func)(int*, int);

int ex(int*a, int b){
    return *a +b;
}

int main(int argc, char const *argv[])
{
    
    func = ex;
    int valor = 5;

    int result = func(&valor, 20);

    printf("%d", result);




    return 0;
}
