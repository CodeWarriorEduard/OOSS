#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void devuelvealgo(int p1, int *p2){

    ++p1;
    ++*p2;
    printf("%d-%d \n", p1, *p2 );
}


int main(int argc, char const *argv[])
{
    int a = 2;
    devuelvealgo(a++, &a);   
    devuelvealgo(a++, &a);   
    printf("%d \n", ++a);

    return 0;
}
