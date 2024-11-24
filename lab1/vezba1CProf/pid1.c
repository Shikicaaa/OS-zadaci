#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main() {

	char buf[SIZE];
	FILE *fajl;

	fajl = fopen("/proc/1/status", "r");

	if (!fajl) {
		printf("Fajl se nije ucitao, proveriti da li postoji direktorijum ili da li ste ispravno uneli putanju");
		return -1;
	}

	while (!feof(fajl)) {
		if (fgets(buf, SIZE, fajl)) {
			printf("%s", buf);
		}
	}

	fclose(fajl);

	fajl = fopen("/proc/1/maps" , "r");

	if (!fajl) {
		printf("Fajl se nije ucitao, proveriti da li postoji direktorijum ili da li ste ispravno uneli putanju");
		return -1;
	}

	while (!feof(fajl)) {
		if (fgets(buf, SIZE, fajl)) {
			printf("%s", buf);
		}
	}

	fclose(fajl);

	return 0;
}
