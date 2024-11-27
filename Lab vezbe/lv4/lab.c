#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
int main(){
    int dv[2];
    char buffer[255];
    if(pipe(dv) != 0){
        printf("GRESKA\n");
    }
    //cale proces
    if(fork() != 0){
        close(dv[0]);
        for(int i = 0;i<25;i++){
            char add = 'A' + rand()%26;
            write(dv[1],&add,sizeof(char));
            printf("Upisao sam: %c\n", add);
        }
        char a = '$';
        write(dv[1],&a,sizeof(char));
        close(dv[1]);
    }else{
        close(dv[1]);
        char c;
        FILE * f = fopen("chars.txt","w");
        while(read(dv[0],&c,sizeof(char))){
            if(c == '$'){
                printf("Kraj streama!\n");
                break;
            }
            fputc(c,f);
            fputc('\n',f);
        }
        close(dv[0]);
        fclose(f);
    }
    return(0);
}