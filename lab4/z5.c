#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	int pd[2];
	char buffer[80];

	if (pipe(pd) < 0) {
		printf("Doslo je do greske pri inicijalizacije datavoda\n");
		return -1;
	}

	if (fork() == 0) {
		close(pd[0]);

		FILE* fajl;
		fajl = fopen("podaci", "r");

		do {
			int daLiJeNULL = fgets(buffer, 80, fajl);
			buffer[strcspn(buffer, "\n")] = '\0';
			if (!daLiJeNULL) {
				write(pd[1], "\0", 0);
				break;
			}
			write(pd[1], buffer, 80);
			printf("Gurnuo sam ovo -> %s <- u datavod\n", buffer);
		} while (!feof(fajl));

		close(pd[1]);

		printf("Zatvaram prodajnu stranu\n");
		exit(0);
	} else {
		close(pd[1]);
		int lenght;

		do {
			lenght = read(pd[0], buffer, 80);
			if (lenght == 0) break;
			printf("velicina lenghta: %d\n", lenght);
			printf("Procitao sam %s\n", buffer);
		} while (lenght != 0);

		printf("Zatvaram potrosacku stranu\n");

		close(pd[0]);
		wait(NULL);
	}
}
