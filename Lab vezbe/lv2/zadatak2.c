#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ARGS 20
int obrada(char * komanda){
    char * argumenti[20];
    int noArgs;
    int ret;
    int pid;
    noArgs = 0;
    argumenti[noArgs++] = strtok(komanda, " \n");
    while((argumenti[noArgs++] = strtok(0,"\n")) != NULL){}
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
            return 0;
        }
    }else{
        return 1;
    }
}
int obrada_dat(char * batch){
    FILE * f;
    char komanda[255];
    int ret = 0;
    f = fopen(batch, "r");
    if(f != 0){
        fgets(komanda,255,f);
        while(!feof(f)){
            ret = obrada(komanda);
            if(ret == 1)
                return ret;
            fgets(komanda,255,f);
        }
    }else{
        printf("Greska prilikom otvaranja .bat fajla");
    }
    return ret;
}
int main(int argc ,char *argv[]){

    char komanda[255];
    int ret = 0;

    do{  
        printf("najjaciprompt>");
        gets(komanda);
        if(komanda[0] == '@'){
            char * batch = strtok(komanda + 1, " ");
            ret = obrada_dat(batch);
        }   
        else{
            ret = obrada(komanda);
        }
    }while(ret == 0);

    

    return 0;
}