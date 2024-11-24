#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
struct argument{
    int size;
    int * niz;
};
void * aritmeticka(void * args){
    struct argument * p = (struct argument*)args;
    int * array = p->niz;
    int n = p->size;
    printf("%d\n",n);
    double s = 0.0;
    int i;
    for(i = 0;i<n;i++){
        printf("%d ",array[i]);
    }
}
int main(int argc, char * argv[]){
    struct argument args;
    args.size = argc-1;
    int * niz = malloc((argc-1)*sizeof(int));
    int i;
    int k = 0;
    for(i = 0;i<args.size;i++){
        niz[k++] = atoi(argv[i+1]); 
    }
    args.size = *niz;
    double * s;
    pthread_t nit;
    pthread_create(&nit,NULL,(void*)aritmeticka,(void*)&args);
    pthread_join(nit,NULL);
    printf("\n");
    return 0;
}