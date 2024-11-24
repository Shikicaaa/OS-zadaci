#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE = 255;

typedef struct {
    int* numbers;
    int count;
    int sum;
} ThreadData;

void *suma(void* args){
   ThreadData * arg = (ThreadData*)args;
   int* array = (int*)malloc(sizeof(int)*arg->count); 
   array = arg->numbers;
   double s = 0.0;
   int i = 0;
   for(i;i<arg->count;i++){
        s += array[i];
   }
   arg->sum = s;
}

int main(){
    FILE * f = fopen("prvi.txt","r");
    if(!f){
        printf("Greska pri otvaranju!");
        return -1;
    }
    char line[255];

    while(!feof(f)){
        fgets(line,255,f);
        int brojevi[255];
        int c = 0;
        char* token = strtok(line, " ");
        while(token){
            brojevi[c++] = atoi(token);
            token = strtok(NULL, " ");
        }
        ThreadData podatak;
        podatak.numbers = brojevi;
        podatak.count = c;
        pthread_t nit;
        pthread_create(&nit, NULL, suma, &podatak);
        pthread_join(nit,NULL);
        printf("Suma niza je = %d\n", podatak.sum);
    }
    return 0;
}
