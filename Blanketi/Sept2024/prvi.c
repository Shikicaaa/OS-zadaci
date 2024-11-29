#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
pthread_t nit;
sem_t semafor[2];
void * function(void * args){
    int * n = (void*)args;
    while(*n != 999){
        sem_wait(&semafor[1]);
        if(*n == 999) break;
        for(int i = 0;i<=*n;i++){
            printf("%d\n",i);
            sleep(2);
        }
        sem_post(&semafor[0]);
    }
    sem_post(&semafor[0]);
}
int main(){
    int arg;
    int * n = &arg;
    sem_init(&semafor[0],0,0);//zakljucan
    sem_init(&semafor[1],0,0);//zakljucan

    pthread_create(&nit,NULL,function,(void*)n);

    printf("Kreirao nit\nUnesi broj: ");
    scanf("%d",&arg);
    sem_post(&semafor[1]);
    while(arg != 999){
        sem_wait(&semafor[0]);
        printf("Unesi broj: ");
        scanf("%d",&arg);
        if(arg == 999) break;
        sem_post(&semafor[1]);
    }
    sem_post(&semafor[1]);
    pthread_join(nit,NULL);
    sem_destroy(&semafor[1]);
    sem_destroy(&semafor[0]);
    return 0;
}