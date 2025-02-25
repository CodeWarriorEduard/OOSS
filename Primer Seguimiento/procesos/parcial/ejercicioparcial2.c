#include<stdio.h>

struct S{
    char a;
    int c;  
    float b;
};


int main(){

    int i=-3, j=2, k=0, m;

    m =++i && ++j || ++k;

    printf("%d, %d, %d, %d \n", i,j,k,m);

    printf("%lu", sizeof(struct S));

}