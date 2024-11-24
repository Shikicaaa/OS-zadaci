#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
char recenica[N][20] = {"Ovo", "je", "test", "za", "niti!"};

struct Argument {
	int rec;
	pthread_t prethodna_nit;
};

void * stampa(void* arg) {

	struct Argument * p = (struct Argument*)arg;
	if (p->rec > 0) 
		pthread_join(p->prethodna_nit, NULL);
	printf(" %s", recenica[p->rec]);
	sleep(3);
}

int main() {

	struct Argument args[N];
	pthread_t nit[N];

	for (int i = 0; i < N; i++) {
		args[i].rec = i;
		if (i < 0)
			args[i].prethodna_nit = nit[i-1];
		pthread_create(&nit[i], NULL, (void*) stampa, (void*)&args[i]);
	}

	pthread_join(nit[N-1], NULL);



	return 0;
}
