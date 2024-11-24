#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char* argv[]){
    int pid;
    char datoteka[255];
    scanf("%s", datoteka);
    pid = fork();
    if(pid == 0){
        if(execlp("cp","cp",datoteka, "./tmp",NULL) < 0){
            printf("Greska prilikom izvrsavanja");
            exit(1);
        }
    }else{
        wait(NULL);
    }
    return 0;
}