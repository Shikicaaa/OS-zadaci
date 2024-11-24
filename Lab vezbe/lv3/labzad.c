#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int mat[50][50];
int n,m;
sem_t mutex1, mutex2;
void * sKol(void* arg){
    int j = *((int *)arg);
    int temp;
    int i,k;
    sem_wait(&mutex1);
    printf("Sortiramo elemente %d. vrste\n",j);
    for(i = 0;i<n-1;i++){
        for(k = i+1;k<n;k++){
            if(mat[j][k] > mat[j][i])
            {
                temp = mat[j][k];
                mat[j][k] = mat[j][i];
                mat[j][i] = temp;
            }
        }
    }
    sleep(1);
    sem_post(&mutex2);
}
void * sVr(void * arg){
    int j = *((int *)arg);
    int temp;
    int i,k;
    sem_wait(&mutex2);
    printf("sortiramo elemente %d. kolone\n",j);
    for(i = 0;i<m-1;i++){
        for(k = i+1;k<m;k++){
            if(mat[k][j] > mat[k][i]){
                temp = mat[k][j];
                mat[k][j] = mat[i][j];
                mat[j][i] = temp;
            }
        }
    }
    sleep(1);
    sem_post(&mutex1);
}
int main(){
    printf("Unesite dimenzije matrice: ");
    scanf("%d%d",&n,&m);
    int i, j;
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<m;j++)
        {
            scanf("%d",&mat[i][j]);
        }
    }
    
    for(i = 0;i<n;i++)
    {
        for(j = 0;j<m;j++)
        {
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }
    sem_init(&mutex1,0,1);
    sem_init(&mutex2,0,1);
    pthread_t prva,druga;
    for(i = 0;i<n;i++){
        pthread_create(&prva,NULL,(void* )sVr,(void* )&i);
        pthread_create(&druga,NULL,(void* )sKol,(void* )&i);
        pthread_join(prva,NULL);
        pthread_join(druga,NULL);
    }

    for(i = 0;i<n;i++)
    {
        for(j = 0;j<m;j++)
        {
            printf("%d\t",mat[i][j]);
        }
        printf("\n");
    }
    sem_destroy(&mutex1);

    sem_destroy(&mutex2);
}
