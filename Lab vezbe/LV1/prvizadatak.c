#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 100
int main(){
    char buf[MAX_BUF];
    char buf1[MAX_BUF];
    char buf2[MAX_BUF];
    FILE * f;
    f = fopen("/proc/meminfo","r");
    if(f == NULL){
        printf("Greska!");
        return -1;
    }
    while(!feof(f)){
        fgets(buf,MAX_BUF,f);
        if(strstr(buf,"MemFree")){
            printf("%s\n",buf);
            int i = 0;
            for(i;buf[i] != '\0';i++){
                if(buf[i] >= '1' && buf[i] <= '9') break;
            }
            int k = 0;
            while(buf[i] != ' '){
                buf1[k++] = buf[i++];
            }
            buf1[k] = '\0';
        }
        if(strstr(buf,"MemTotal")){
            printf("%s\n",buf);
            int i = 0;
            for(i;buf[i] != '\0';i++){
                if(buf[i] >= '1' && buf[i] <= '9') break;
            }
            int k = 0;
            while(buf[i] != ' '){
                buf2[k++] = buf[i++];
            }
            buf2[k] = '\0';
        }
    }
    int a = 0;
    for(int i;buf1[i] != '\0';i++){
        a = a*10 + (buf1[i] - '0');
    }
    int b = 0;
    for(int i;buf2[i] != '\0';i++){
        b = b*10 + (buf2[i] - '0');
    }
    printf("Preostalo prostora: %d", b-a);
    fclose(f);
    return 1;
}