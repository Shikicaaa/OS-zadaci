#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {
	char buf[SIZE];
	char name[SIZE], size[SIZE];
	FILE *fajl;

	fajl = fopen("/proc/partitions", "r");

	if (!fajl) {
		printf("Doslo je greske prilikom otvaranja fajla");
		return -1;
	}


	while (!feof(fajl)) {

		int i = 0;
		for (int i = 0; i < 4; i++) {
			if (i == 3) { //name
				fscanf(fajl, "%s", name);
			}
			if (i == 2) { //size
				fscanf(fajl, "%s", size);
			}
			else {
				fscanf(fajl, "%s", buf);
			}
		}
		printf("Name: %s & size: %s\n", name, size);
	}

	return 0;
}
