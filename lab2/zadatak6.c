#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 3

int niz[N][N];

void * sortiraj(void * arg) {
	int k = *((int*)arg);
	printf("%d\n",k);
	fflush(stdout);

	for (int i = 0; i < N - 1; i++) {
		for (int j = i+1; j < N; j++) {
			if (niz[k][i] > niz[k][j]) {
				int pom = niz[k][i];
				niz[k][i] = niz[k][j];
				niz[k][j] = pom;
			}
		}
	}

}

int main() {

	int n = N, m = N;

	pthread_t nit[N];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &niz[i][j]);
		}
	}

	int k;

	for (k = 0; k < n; k++) {
		int* row = (int*)malloc(sizeof(int));
		*row = k;
		printf("%d\n",k);
		pthread_create(&nit[k], NULL, (void*) sortiraj, (void *)(row));
	}

	for (k = 0; k < n; k++) {
		pthread_join(nit[k], NULL);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", niz[i][j]);
		}
		printf("\n");
	}

	return 0;
}

