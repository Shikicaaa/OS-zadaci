#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TRUE 1
#define FALSE 0

int buff[2];

pthread_mutex_t mutex;
pthread_cond_t condvarFull;
pthread_cond_t condvarEmpty;

int bufferFull = FALSE;

void * funkcija(void* args){
    long int rnd; 
    float normalizedRnd;
    int sleepTime;
    int i;
    int buffPointer;
    buffPointer = 0;
    for(i = 1;i<=10;i++)
    {
        rnd = random();
        normalizedRnd = (float)rnd/(float)RAND_MAX;
        sleepTime = (int)(normalizedRnd * 5);
        pthread_mutex_lock(&mutex);
        while(bufferFull)
        {
            pthread_cond_wait(&condvarEmpty,&mutex);
        }
        buff[buffPointer] = i;
        printf("Thread u buffer %d upisao vrednost %d\n",buffPointer,i);

        buffPointer = (buffPointer+1)%2;
        if(buffPointer == 0){
            bufferFull = TRUE;
        }
        pthread_cond_signal(&condvarFull);
        pthread_mutex_unlock(&mutex);
        sleep(sleepTime);
    }
}
int main(){
    pthread_t threadID;
    int i;

    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&condvarEmpty,NULL);
    pthread_cond_init(&condvarFull,NULL);

    pthread_create(&threadID,NULL,funkcija,NULL);

    for(i = 0;i<5;i++){
        pthread_mutex_lock(&mutex);
        while(!bufferFull){
            pthread_cond_wait(&condvarFull,&mutex);
        }
        printf("Zbir brojeva iz buffera je %d + %d = %d\n",buff[0],buff[1],buff[0]+buff[1]);
        bufferFull = FALSE;
        pthread_cond_signal(&condvarEmpty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condvarEmpty);
    pthread_cond_destroy(&condvarFull);
    return 0;
}