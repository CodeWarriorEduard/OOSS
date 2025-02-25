#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mFuel;
pthread_cond_t condFuel;
int fuel = 0;
void *filling(){
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&mFuel);
        fuel+=15;
        printf("Filling the car \n");
        pthread_mutex_unlock(&mFuel);
        pthread_cond_signal(&condFuel);
        sleep(1);
    }
}


void *car(void* args){
    pthread_mutex_lock(&mFuel);
    while (fuel<40)
    {
        printf("Not fuel, waiting to fill \n");
    }
    
}

int main(int argc, char const *argv[])
{
    pthread_t th[2];
    for (int i = 0; i < 2; i++)
    {
        
    }
    
    
    return 0;
}
