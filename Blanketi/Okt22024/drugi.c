#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(){

    int pd1[2];
    int pd2[2];
    pipe(pd1);
    pipe(pd2);
    if(fork() != 0){
        close(pd1[0]);
        close(pd2[1]);
        //cale proces
        char buffer[256];
        printf("Unesi putanju i kljucnu rec: ");
        gets(buffer);
        write(pd1[1],buffer,strlen(buffer)+1);
        int linija;
        read(pd2[0],&linija,sizeof(int));
        while(linija != -1){
            printf("Linija na kojoj se nalazi kljucna rec je %d\n",linija);
            read(pd2[0],&linija,sizeof(int));
        }
        close(pd1[0]);
        close(pd2[0]);
        wait(NULL);
    }else{
        //dete proces
        close(pd1[1]);
        close(pd2[0]);
        char buffer[256];
        read(pd1[0],buffer,256);
        char * fajl = strtok(buffer, " ");
        char * rec = strtok(NULL, " ");
        FILE * f = fopen(fajl, "r");
        char linija[256];
        int l = 1;
        while(!feof(f)){
            fgets(linija,256,f);
            if(strstr(linija,rec)){
                write(pd2[1],&l,sizeof(int));
            }
            l++;
        }
        l = -1;
        write(pd2[1],&l,sizeof(int));
        close(pd2[1]);
        close(pd1[0]);
        fclose(f);
    }
}