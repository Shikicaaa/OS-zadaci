#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BUF 100
int main(){
    char buffer[MAX_BUF];
    FILE* f;
    f = fopen("/proc/cpuinfo","r");
    if(f == NULL){
        printf("Fajl nije ucitan.");
        return -1;
    }
    while(!feof(f)){
        fgets(buffer,MAX_BUF,f);
        if(strstr(buffer,"cpu MHz")){
            puts(buffer);
            return 1;
        }
    }
    printf("Desila se neka greska.");
    return 0;
}