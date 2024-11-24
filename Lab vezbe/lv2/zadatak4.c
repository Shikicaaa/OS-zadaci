#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int i;
    char** argumenti = (char**)malloc((argc+1)*sizeof(char*));//alociramo adresu za niz stringova duzine argc i +1 za NULL
    argumenti[0] = (char*)malloc((strlen("./zadatak4a")+1)*sizeof(char));//za prvi argument se zauzima dovoljno memorije
    //koliko ima i ovaj string + 1 za \0
    strcpy(argumenti[0],"./zadatak4a");
    for(int i = 1;i<argc;i++){
        argumenti[i] = (char*)malloc((strlen(argv[i])+1)*sizeof(char));
        strcpy(argumenti[i],argv[i]);
    }
    argumenti[argc] = NULL;
    int pid = fork();
    if(pid == 0){
        if(execv("./zadatak4a",argumenti) < 0){
            printf("doslo je do greske!");
            exit(1);
        }
    }else
    {
        wait(NULL);
    }
    for(int i = 0;i<argc;i++){
        free(argumenti[i]);
    }
    free(argumenti);
    return 0;

}