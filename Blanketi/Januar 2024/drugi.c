#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    int pd1[2];
    int pd2[2];
    if(pipe(pd1) < 0){
        printf("Greska\n");
        exit(-1);
    }
    if(pipe(pd2) < 0){
        printf("Greska2\n");
        exit(-1);
    }

    if(fork() != 0){
        //cale
        close(pd2[0]);
        close(pd1[1]);
        char rec[50];
        int sum;
        printf("Unesi rec: ");
        gets(rec);
        while(strcmp(rec,"kraj") != 0){
            write(pd2[1],rec,strlen(rec)+1);
            int count;
            if((count = read(pd1[0],&sum,sizeof(int))) != 0 && strcmp(rec,"kraj") != 0){
                printf("Suma brojeva u <%s> je <%d>\n",rec,sum);
                printf("Unesi rec: ");
                gets(rec);
            }
        }
        close(pd1[0]);
        close(pd2[1]);
        wait(NULL);
    }else{
        //child
        close(pd2[1]);
        close(pd1[0]);
        char rec[50];
        char buffer[10];
        read(pd2[0],rec,50);
        while(strcmp(rec,"kraj") != 0){
            int sum = 0;
            int i = 0;
            int c = 0;
            for(int j = 0;j<strlen(rec)+1;j++){
                if(rec[j] >= '0' && rec[j] <= '9'){
                    buffer[i++] = rec[j];
                }else if(i != 0){
                    sum += atoi(buffer);
                    i = 0;
                    memset(buffer,'\0',10);
                }
            }
            write(pd1[1],&sum,sizeof(int));
            read(pd2[0],rec,50);
        }
        close(pd1[1]);
        close(pd2[0]);
    }
}