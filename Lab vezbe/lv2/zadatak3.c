#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define ARGS 20
void * obrada(void * arg){
    char * komanda = (char*) arg;
    char * argumenti[20];
    int noArgs;
    int ret;
    int pid;
    noArgs = 0;
    argumenti[noArgs++] = strtok(komanda, " ");
    while((argumenti[noArgs++] = strtok(0," ")) != NULL){}
    if(strcmp(komanda, "logout") != 0){
        pid = fork();
        if(pid == 0){
            sleep(5);
            if(strcmp(argumenti[noArgs-2], "&") == 0){
                argumenti[noArgs-2] = NULL;
            }
            execvp(argumenti[0], argumenti);
            printf("Greska pri izvrsenju komande!\n");
            exit(-1);
        }else{
            if(strcmp(argumenti[0-2], "&") != NULL){
                wait(&ret);
            }
            ret = 0;

        }
    }else{
        return 1;
    }
    return 0;
}
int main(int argc ,char *argv[]){

    char komanda[255];
    int ret = 0;
    pthread_t nit;
    do{  
        printf("najjaciprompt>");
        gets(komanda);
        pthread_create(&nit,NULL,(void*)obrada,(void*)komanda);
        //pthread_create(adresa niti koju kreiramo, ogranicenje, void pokazivac na f-ju, void pokazivac na argument);

        pthread_join(nit, &ret);
        //pthread_join(nit, adresa mesta na kojem belezimo return status);
    }while(ret == 0);

    

    return 0;
}