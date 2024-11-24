#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 20
#define MAX_ARG_LENGHT 100

int main(int argc, char * argv[]) {
	char * args[MAX_ARGS];

	args[0] = (char*)malloc(MAX_ARG_LENGHT * sizeof(float));
	strcpy(args[0], "zadatak4a");

	for (int i = 1; i < argc; i++) {
		args[i] = (char*)malloc(MAX_ARG_LENGHT * sizeof(float));
		strcpy(args[i], argv[i]);
	}
	args[argc] = NULL;

	if (fork() == 0) {
		sleep(5);
		if (execv("./zadatak4a", args) < 0) {
			printf("Doslo je do greske\n");
			exit(1);
		}
	} else {
		printf("--------------------\n");
		wait(NULL);
	}

	for (int i = 0; i< argc; i++) {
		free(args[i]);
	}

	return 0;
}
