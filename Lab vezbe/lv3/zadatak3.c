#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int niz[20];
pthread_mutex_t mutex1, mutex2;

void* nit1(void * args){
    int pos;
    while(1){
        pthread_mutex_lock(&mutex1);
        pos = rand()%10;
        niz[pos] = rand()%100 + 1;
        printf("Prva nit je upisala na poziciju %d broj %d\n",pos,niz[pos]);
        pthread_mutex_unlock(&mutex1);
        sleep(2);
    }
}

void* nit2(void * args){
    int pos;
    while(1){
        pthread_mutex_lock(&mutex2);
        pos = rand()%10+10;
        niz[pos] = rand()%100 + 1;
        printf("Druga nit je upisala na poziciju %d broj %d\n",pos,niz[pos]);
        pthread_mutex_unlock(&mutex2);
        sleep(4);
    }
}


void* nit3(void * args){
    int pos;
    while(1){
        pthread_mutex_lock(&mutex2);
        pthread_mutex_lock(&mutex1);
        pos = rand()%20;
        niz[pos] = rand()%100 + 1;
        printf("Treca nit je upisala na poziciju %d broj %d\n",pos,niz[pos]);
        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);

       sleep(8);

    }
}

int main(){
    pthread_t n1,n2,n3;
    pthread_mutex_init(&mutex1,NULL);
    pthread_mutex_init(&mutex2,NULL);

    
    pthread_create(&n1,NULL,(void*)&nit1,NULL);
    pthread_create(&n2,NULL,(void*)&nit2,NULL);
    pthread_create(&n3,NULL,(void*)&nit3,NULL);
    pthread_join(n1,NULL);
    pthread_join(n2,NULL);
    pthread_join(n3,NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
} 