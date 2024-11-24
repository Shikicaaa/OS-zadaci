#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

const char Reci[5][50] = {"Ovo", "je", "test", "za", "semaphore!"};

sem_t Semafori[4];

void* stampaj(void* arg) {
	int p = *((int*)arg);

	if (p > 0) {
		sem_wait(&Semafori[p-1]);
	}

	printf("%s ", Reci[p]);

	if (p < 4) {
		sem_post(&Semafori[p]);
	}

	sleep(3);
	printf("%d\n", p);

}

int main() {
	int args[5];
	pthread_t nit[5];

	for (int i = 0; i < 4; i++) {
		sem_init(&Semafori[i], 0, 0);
	}


	for (int i = 0; i < 5; i++) {
		args[i] = i;
		pthread_create(&nit[i], NULL, (void*)stampaj, (void*)&args[i]);
	}


	for (int i = 0; i < 5; i++) {
		pthread_join(nit[i], NULL);
	}

	return 0;
}
