#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>

int main() {
	int pd1[2], pd2[2];
	// pd sa indeksom 0 je vezano za dateta, a sa indeksom 1 za rod.
	if (pipe(pd1) == -1) {
		printf("Greska prilikom kreiranja prvog datavoda\n");
		return -1;
	}

	if (pipe(pd2) == -1) {
		printf("Greska prilikom kreiranja drugog datavoda\n");
		return -1;
	}

	if (fork() != 0) {
		printf("Kreiran je Prvi proces\n");
		char buffer[100];
		//U roditelju smo!
		close(pd1[0]);
		close(pd2[0]);
		close(pd2[1]);
		do {
			gets(buffer);
			write(pd1[1], buffer, strlen(buffer) + 1);
			printf("Prvi proces poslao u pd1: %s\n", buffer);
		} while (strcmp(buffer, "KRAJ") != 0);

		printf("Prvi proces primio KRAJ\n");
		wait(NULL);
		close(pd1[1]);
		//zatvaramo roditelja kojeg smo koristili!
		printf("Prvi proces izlazi\n");
		return 0;
		//ovo mi nije jasno!
	} else if (fork() != 0) {
		printf("Kreiran drugi proces\n");
		//MORAMO DA NAPRAVIMO DRUGU LINIJU
		char buffer1[100];
		close(pd1[1]);
		close(pd2[0]);
		do {
			read(pd1[0], buffer1, 100);
			printf("Drugi proces primio: %s\n", buffer1);
			buffer1[0] = toupper(buffer1[0]);
			write(pd2[1], buffer1, strlen(buffer1) + 1);
			printf("Drugi proces poslao %s\n", buffer1);
		} while (strcmp(buffer1, "KRAJ") != 0);

		printf("Drugi proces primio KRAJ\n");
		wait(NULL);
		close(pd1[0]);
		close(pd2[1]);
		printf("Drugi proces izlazi\n");
		exit(0);
	} else {
		char buffer2[100];
		printf("Kreiran treci proces");
		close(pd1[0]);
		close(pd1[1]);
		close(pd2[1]);
		do {
			read(pd2[0], buffer2, 100);
			printf("Treci proces primio: %s\n", buffer2);
			if (buffer2[strlen(buffer2) - 1] != '.') {
				buffer2[strlen(buffer2) + 1] = '\0';
				buffer2[strlen(buffer2)] = '.';
			}
			printf("Modifikovana recenica %s\n", buffer2);
		} while (strcmp(buffer2, "KRAJ.") != 0);

		printf("Treci proces primio KRAJ\n");
		close(pd2[0]);
		printf("Treci proces Izlazi!\n");
		exit(0);
	}
}


		


