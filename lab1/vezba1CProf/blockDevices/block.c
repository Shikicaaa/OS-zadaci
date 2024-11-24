#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

int main() {
	char buf[SIZE];
	char flag = 0;
	FILE *fajl;
	fajl= fopen("/proc/devices", "r");
	
	if (!fajl) {
		printf("Datoteka nije ucitana");
		return -1;
	}

	
	while (!feof(fajl)) {
		fgets(buf, SIZE, fajl);
		if (strstr(buf, "Block devices:")) {
			flag = 1;
			break;
		}
	}	

	if (!flag) {
		printf("Nema blokiranih uredjaja");
		return -1;
	}


	while (!feof(fajl)) {
		fgets(buf, SIZE, fajl);
		printf("%s\n", buf);
	}


	return 0;
}
