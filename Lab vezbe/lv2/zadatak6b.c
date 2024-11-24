#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define n 4
int a[n][n];
void * sort(void * arg){
    int k = *((int *)arg);
    int i, j, pom;
    printf("Sortiranje vrste %d\n",k);
    for(i = 0;i<n-1;i++){
        for(j = i+1;j<n;j++){
            if(a[k][i] > a[k][j]){
                pom = a[k][i];
                a[k][i] = a[k][j];
                a[k][j] = pom;
            }
        }
    }
    free(arg);
}
int main(){
    int i,j, *row;
    pthread_t niti[n];
    for(i = 0;i<n;i++){
        for(j = 0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    for(i = 0;i<n;i++){
        for(j = 0;j<n;j++){
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
    for(i = 0;i<n;i++){
        row = (int*)malloc(sizeof(int));
        *row = i;
        pthread_create(&niti[i],NULL,(void*)sort,(void*)row);
        pthread_join(niti[i],NULL);
    }

    for(i = 0;i<n;i++){
        for(j = 0;j<n;j++){
            printf("%d\t",a[i][j]);
        }
        printf("\n");
    }
}