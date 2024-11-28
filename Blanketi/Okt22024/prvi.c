#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>


sem_t prviSem, drugiSem;
void * prva(void* args){
    char* fajl = (char*)malloc(sizeof(char)*(strlen((char*)args)+1));
    strcpy(fajl,(char* )args);
    puts(fajl);
    FILE * glavni = fopen(fajl, "r");
    int linija = 1;
    char buff[256];
    while(!feof(glavni)){
        sem_wait(&prviSem);
        printf("Prvi pise\n");
        FILE * upisni = fopen("zbir.txt","a");
        fgets(buff,255,glavni);
        fprintf(upisni, "%s %d %s",fajl,linija,buff);
        fclose(upisni);
        sem_post(&drugiSem);
        linija++;
    }
    fclose(glavni);
}

void * druga(void* args){
    char* fajl = (char*)malloc(sizeof(char)*(strlen((char*)args)+1));
    strcpy(fajl,(char* )args);
    puts(fajl);
    FILE * glavni = fopen(fajl, "r");
    int linija = 1;
    char buff[256];
    char final[320] = {};
    while(!feof(glavni)){
        sem_wait(&drugiSem);
        printf("Drugi pise\n");
        FILE * upisni = fopen("zbir.txt","a");
        fgets(buff,255,glavni);
        fprintf(upisni, "%s %d %s",fajl,linija,buff);
        fclose(upisni);
        sem_post(&prviSem);
        linija++;
    }
    fclose(glavni);
}

int main(int argc, char* argv[]){
    pthread_t nit1, nit2;
    sem_init(&prviSem,0,1);
    sem_init(&drugiSem,0,0);
    pthread_create(&nit1,NULL,prva,(void*)argv[1]);
    pthread_create(&nit2,NULL,druga,(void*)argv[2]);
    pthread_join(nit1,NULL);
    pthread_join(nit2,NULL);
    sem_destroy(&prviSem);
    sem_destroy(&drugiSem);
}
