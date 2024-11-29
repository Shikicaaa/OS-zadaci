#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char * argv[]){
    int pd[2];
    pipe(pd);
    if(fork() != 0){
        close(pd[0]);
        //cale
        FILE * f = fopen(argv[1], "r");
        char c;
        int count = 1;
        while(!feof(f) && count <= 1000){
            c = fgetc(f);
            write(pd[1],&c,1);
            count++;
        }
        close(pd[1]);
        fclose(f);
        wait(NULL);
    }else{
        close(pd[1]);
        FILE * f = fopen("izlaz.txt","w");
        int count = 1;
        char c;
        char novi;
        while(read(pd[0],&c,1)){
            novi = c ^ count;
            fputc(novi,f);
            count++;
        }
        while(count <= 1000){
            novi = '\0' ^ count;
            fputc(novi,f);
            count++;
        }
        fclose(f);
        close(pd[0]);
    }
}