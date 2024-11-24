#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ARGS 20
int main(int argc ,char *argv[]){

    char komanda[255];
    char *argumenti[20];
    int numArgs = 0;
    int status;

    printf("najjaciprompt>");
    gets(komanda);
    argumenti[numArgs++] = strtok(komanda, " ");

    while((argumenti[numArgs++] = strtok(0, " ")) != NULL){
    }

    while(strcmp(komanda,"logout") != 0){
        if(fork() == 0){//u child procesu
            sleep(5);
            if(strcmp(argumenti[numArgs-2], "&") == 0){
                argumenti[numArgs-2] = NULL;
            }
            execvp(argumenti[0],argumenti);
            printf("Greska pri izvrsenju komande!");
            exit(-1);
        }else{
            if (strcmp(argumenti[numArgs-2],"&") != 0) {
                wait(&status);
            }
        }
            printf("najjaciprompt>");
            gets(komanda);
            numArgs = 0;
            argumenti[numArgs++] = strtok(komanda," ");
            while ((argumenti[numArgs++] = strtok(0, " ")) != NULL) {}
    }

    return 0;
}