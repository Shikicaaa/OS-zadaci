#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int Niz[20];

pthread_mutex_t Mutex1, Mutex2;

void * nit1(void * args) {
	int pos;

	while(42) {
		pthread_mutex_lock(&Mutex1);

		pos = rand() % 10;
		Niz[pos] = rand() & 100;

		printf("Prva nit je na pozicija %d upisala vrednost %d\n", pos, Niz[pos]);
		pthread_mutex_unlock(&Mutex1);

		sleep(2);
	}
}

void * nit2(void * args) {
	int pos;

	while(42) {
		pthread_mutex_lock(&Mutex2);

		pos = 10 + rand() % 10;
		Niz[pos] = rand() & 100;

		printf("Druga nit je na pozicija %d upisala vrednost %d\n", pos, Niz[pos]);
		pthread_mutex_unlock(&Mutex2);

		sleep(4);

	}
}

void * nit3(void * args) {
	int pos;

	while(42) {
		pthread_mutex_lock(&Mutex1);
		pthread_mutex_lock(&Mutex2);

		pos = 10 + rand() % 20;
		Niz[pos] = rand() & 100;

		printf("Treca nit je na pozicija %d upisala vrednost %d\n", pos, Niz[pos]);
		pthread_mutex_unlock(&Mutex1);
		pthread_mutex_unlock(&Mutex2);

		sleep(8);

	}
}

int main() {
	pthread_t t1, t2, t3;
	
	pthread_create(&t1, NULL, (void*)nit1, (void*)NULL);
	pthread_create(&t2, NULL, (void*)nit2, (void*)NULL);
	pthread_create(&t3, NULL, (void*)nit3, (void*)NULL);

	pthread_mutex_init(&Mutex1, NULL);
	pthread_mutex_init(&Mutex2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	pthread_mutex_destroy(&Mutex1);
	pthread_mutex_destroy(&Mutex2);

	return 0;
}


