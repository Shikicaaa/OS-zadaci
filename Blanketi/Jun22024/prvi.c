#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * prva(void* args){
    int n = *((int *)args);
    int i;
    for(i = 0;i<=n;i++){
        printf("Prva nit stampa: %d\n",i);
        fflush(stdout);
    }
}

void * druga(void* args){
    int n = *((int *)args);
    int i = 7;
    while(i <= n){
        printf("Druga nit stampa: %d\n",i);
        fflush(stdout);
        i +=7;
    }
}
int main(){
    int n;
    pthread_t prvaNit;
    pthread_t drugaNit;
    printf("Unesi N: ");
    scanf("%d",&n);
    pthread_create(&prvaNit, NULL, &prva, (void*)&n);
    pthread_create(&drugaNit, NULL, &druga, (void*)&n);
    pthread_join(prvaNit,NULL);
    pthread_join(drugaNit,NULL);
}