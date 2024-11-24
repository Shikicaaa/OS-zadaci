#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 4
int a[N][N];
void * sortiranje(void * arg){
    int k = *((int *)arg);
    int i, j, pom;
    printf("Sortiranje vrste: %d\n",k);
    fflush(stdout);
    for(int i =0;i<N-1;i++){
        for(int j = i+1;j<N;j++){
            if(a[k][i] > a[k][j]){
                pom = a[k][i];
                a[k][i] = a[k][j];
                a[k][j] = pom;
            }
        }
    }
}
int main(){
    int i,j;
    pthread_t niti[N];
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    for(int i = 0;i<N;i++){
        pthread_create(&niti[i],NULL,(void*)sortiranje, (void*) &i);
        pthread_join(niti[i],NULL);
    }
    /*for(int i = 0;i<N;i++){
        pthread_join(niti[i],NULL);
    }*/

    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    return 0;
}