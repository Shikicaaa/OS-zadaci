#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 100

int main() {
	char buf[SIZE];
	gets(buf);

	if (fork() == 0) {
		if (execlp("cp", "cp", buf, "./tmp", NULL) < 0) {
			printf("Doslo je do greske\n");
			exit(1);
		}
	} else {
		wait(NULL);
	}
	return 0;
}
