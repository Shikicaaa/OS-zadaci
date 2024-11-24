#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N1 10
#define N2 5
#define N3 7

int buf1[10];
int buf2[5];
int buf3[7];

int empty1 = N1;
int empty2 = N2;
int empty3 = N3;

int head1 = 0;
int tail1 = 0;
int head2 = 0;
int tail2 = 0;
int head3 = 0;
int tail3 = 0;

sem_t mutex1, mutex2, mutex3, mutexempty;

void * nit0(void* args){
    int data;
    while(1){
        sleep(rand()%3);
        sem_wait(&mutexempty);
        printf("Generisanje podataka\n");

        sem_wait(&mutex3);
        if(empty3 > 0)
        {
            buf3[tail3] = rand()%1000;
            tail3 = (tail3 + 1) % N3;
            empty3--;
            sem_post(&mutex3);
            continue;
        }
        else{
            sem_post(&mutex3);
        }
        //pokusavamo u b1 da upisemo
        if(empty1>0){
            buf1[tail1] = rand()%1000;
            tail1 = (tail1+1) % N1;
            empty1--;
            sem_post(&mutex1);
            continue;
        }else{
            sem_post(&mutex1);
        }
        //pokusavamo u b2 da upisemo
        if(empty2>0){
            buf2[tail2] = rand()%1000;
            tail2 = (tail2+1)%N2;
            empty2--;
            sem_post(&mutex2);
            continue;
        }
        else
            sem_post(&mutex2);
    }
}
void * nit1(void * args){
    while (1)
    {
        sem_wait(&mutex1);
        if(empty1 < N1){
            printf("Nit1 je procitala podatak %d\n",buf1[head1]);
            head1 = (head1+1)%N1;
            empty1++;
            //obavestava n0 da se oslobodilo neko mesto.
            sem_post(&mutexempty);
        }
        sem_post(&mutex1);
        sleep(rand()%5);
    }
    
}
void * nit2(void * args){
    while(1){
        sem_wait(&mutex2);
        if(empty2 <N2){
            printf("Nit2 je procitala podatak %d\n",buf2[head2]);
            head2 = (head2+1)%N2;
            empty2++;
            sem_post(&mutexempty);
        }
        sem_post(&mutex2);
        sleep(rand()%7);
    }
}
void * nit3(void * args){
    while(1){
        sem_wait(&mutex3);
        if(empty3 <N3){
            printf("Nit3 je procitala podatak %d\n",buf3[head3]);
            head3 = (head3+1)%N3;
            empty3++;
            sem_post(&mutexempty);
        }
        sem_post(&mutex3);
        sleep(rand()%9);
    }
}
int main(){
    int i;
	/*Identifikatori nit, */
	pthread_t niti[4];
	srand(3232234);

	/*Kreiranje i inicijalizacija semafora*/
	sem_init(&mutex1, 0, 1);
	sem_init(&mutex2, 0, 1);
	sem_init(&mutex3, 0, 1);

	/*semafor mutex_empty pamti ukupan broj slobodnih pozicija u sva tri bafera*/
	sem_init(&mutexempty, 0, N1 + N2 + N3);

	/*Kreiranje niti N0, N1, N3 i N3*/
	pthread_create(&niti[1], NULL, (void *)nit1, (void *)NULL);
	pthread_create(&niti[2], NULL, (void *)nit2, (void *)NULL);
	pthread_create(&niti[3], NULL, (void *)nit3, (void *)NULL);
	pthread_create(&niti[0], NULL, (void *)nit0, (void *)NULL);

	/*Ceka se da se niti zavrse*/
	for(i = 0; i < 4; i++)
		pthread_join(niti[i], NULL);

	/*Brisanje semafora*/
	sem_destroy(&mutex1);
	sem_destroy(&mutex2);
	sem_destroy(&mutex3);
	sem_destroy(&mutexempty);
    return 0;
}