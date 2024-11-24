#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t Mutex;
pthread_cond_t CondVarFull;
pthread_cond_t CondVarEmpty;

int Buffer[2];

int BufferFull = 0; //isto ko da je false!

void* funkcija(void* arg) {
	long int rnd;
	float normalizedRnd;
	int bufferPointer = 0;
	for (int i = 0; i < 10; i++) {
		rnd = random();
		normalizedRnd = (float)rnd/(float)RAND_MAX;
		int sleepTime = (int)(normalizedRnd * 5);
		pthread_mutex_lock(&Mutex);

		while (BufferFull) {
			pthread_cond_wait(&CondVarEmpty, &Mutex);
		}

		Buffer[bufferPointer] = i;
		printf("Thread u buffer[%d] upisao vrednost %d\n", bufferPointer, i);
		bufferPointer = (bufferPointer+1)%2;

		if (bufferPointer == 0) {
			BufferFull = 1;
		}

		pthread_cond_signal(&CondVarFull);
		pthread_mutex_unlock(&Mutex);
		sleep(sleepTime);

	}
}

int main() {
	pthread_t threadID;
	pthread_create(&threadID, NULL, funkcija, NULL); 

	pthread_mutex_init(&Mutex, NULL);
	pthread_cond_init(&CondVarFull, NULL);
	pthread_cond_init(&CondVarEmpty, NULL);

	for (int i = 0; i < 5; i++) {
		pthread_mutex_lock(&Mutex);
		while (!BufferFull) {
			pthread_cond_wait(&CondVarFull, &Mutex);
		}

		printf("Zbir brojeva iz bafera %d + %d = %d\n", Buffer[0], Buffer[1], Buffer[0]+Buffer[1]);

		BufferFull = 0;
		pthread_cond_signal(&CondVarEmpty);
		pthread_mutex_unlock(&Mutex);
	}

	pthread_join(threadID, NULL);

	pthread_mutex_destroy(&Mutex);
	pthread_cond_destroy(&CondVarFull);
	pthread_cond_destroy(&CondVarEmpty);

	return 0;
}


