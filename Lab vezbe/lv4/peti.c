#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]){
    int pid;
    int pd[2];
    char buffer[80];
    FILE * f;
    int c = 0;
    if(pipe(pd) < 0){
        printf("Doslo je do greske");
        return 1;
    }
    pid = fork();
    if(pid < 0){
        printf("Doslo je do greske?!?!");
        return 1;
    }
    //da li je ovo dete?!?!?
    if(pid == 0){
        close(pd[0]);
        f = fopen("treci.txt","r");
        fgets(buffer,80,f);
        while(!feof(f)){
            write(pd[1],buffer,80);
            fgets(buffer,80,f);
        }
        printf("Zatvoren predajnik\n");
        close(pd[1]);
    }
    else{
        close(pd[1]);
        while(1){
            c = read(pd[0],buffer,80);
            if(c == 0){
                printf("Procitao sam 0\n");
                break;
            }
            printf("%s",buffer);
        }
        close(pd[0]);
    }
}