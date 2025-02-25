#include<stdio.h>
int main(int argc, char const *argv[])
{
    int val = 5;
    int *p = &val;
    int **p2 = &p;
    int ***p3 = &p2;
    ***p3 = 2;
    printf("%d", val);

    return 0;
}
