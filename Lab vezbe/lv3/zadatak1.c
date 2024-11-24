#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>


#define N 5
sem_t semafori[N-1];
char reci [N][20] = {"Ovo", "je", "test", "za", "semafor."};

void* stampanje(void * arg){
    int p = *((int*)arg);
    if(p > 0)
        sem_wait(&semafori[p-1]);
    printf("%s",reci[p]);
    if(p < 4)
        sem_post(&semafori[p]);
    sleep(3);
}
int main(){
    int i;
    int args[N];
    pthread_t niti[N];
    for(i = 0;i<N-1;i++){
        sem_init(&semafori[i],0,0);
    }
    for(i = 0;i<N;i++)
    {
        args[i] = i;
        pthread_create(&niti[i],NULL,(void*)stampanje,(void*)&args[i]);
    }
    for(i = 0;i<N;i++)
    {
        pthread_join(niti[i],NULL);
    }
}
