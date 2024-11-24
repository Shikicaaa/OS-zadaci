#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[]){
    int i;
    char* argumenti[4];
    int pid;
    char datoteka[255];
    scanf("%s",datoteka);
    argumenti[0] = (char* )malloc(255*sizeof(char));
    strcpy(argumenti[0],"cp");
    argumenti[1] = (char*)malloc(255*sizeof(char));
    strcpy(argumenti[1],datoteka);
    argumenti[2] = (char*)malloc(255*sizeof(char));
    strcpy(argumenti[2],"./tmp");
    argumenti[3] = NULL;
    pid = fork();
    if(pid == 0){
        if(execvp("cp",argumenti) < 0){
            printf("Greska!");
            exit(1);
        }
    }else{
        wait(NULL);
        for(i = 0;i<3;i++){
            free(argumenti[i]);
        }
    }
    return 0;
}