#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int A = 0;
int N = 0;

sem_t mutexbp, mutexN;

void read_database(int i){
    printf("Baza je procitala %d\n",i);
    sleep(rand()%5);
}

void write_database(){
    printf("Pisac menja vrednost u bazi podataka\n");
    A = A + rand()%10;
	sleep(rand()%5);
}

void * pisac(void * arg)
{
    while(1)
    {
        /*Pristup bazi je smesten u KS*/
        sem_wait(&mutexbp);
        write_database();
        sem_post(&mutexbp);
        /*Pravi pauzu pre sledeceg pristupa bazi podataka*/
        sleep(rand() % 10);
        }
}

void * citalac(void * arg)
{
	int i;
	i = *((int *)arg);
	while(1)
	{
		/*Promenljivoj N se pristupa u KS*/
		sem_wait(&mutexN);

		/*Povecava se broj citalaca*/
		N++;
		/*Prvi citalac zakljucava bazu podataka kako bi sprecio pisca da joj pristupa*/
		if (N == 1)
			sem_wait(&mutexbp);
        
        //posalji signal i otkljucaj se
		sem_post(&mutexN);

		read_database(i);

		/*Promenljivoj N se pristupa u KS*/
		sem_wait(&mutexN);

		/*Smanjuje se broj citalaca*/
		N--;

		/*Poslednji citalac otkljucava bazu podataka*/
		if (N==0)
			sem_post(&mutexbp);

		sem_post(&mutexN);

		/*Pravi pauzu pre sledeceg pristupa bazi podataka */
		sleep(rand() % 7);
	}
}

int main()
{
	int i;
	int red_br[4];

	/*Identifikatori nit, 4 citaoca + 1 pisac*/
	pthread_t niti[5];
	srand(3232234);

	/*Kreiranje i inicijalizacija semafora*/
	sem_init(&mutexN, 0, 1);
	sem_init(&mutexbp, 0, 1);

	/*Kreiranje citalaca i pisca*/
	for (i = 0; i < 4; i++)
	{ 
		red_br[i] = i;
		pthread_create(&niti[i], NULL, (void *)citalac, (void *)&red_br[i]);
	}

	pthread_create(&niti[4], NULL, (void *)pisac, (void *)NULL);

	/*Ceka se da se niti zavrse*/
	for(i = 0; i < 5; i++)
		pthread_join(niti[i], NULL);

	/*Brisanje semafora*/
	sem_destroy(&mutexN);
	sem_destroy(&mutexbp);
}