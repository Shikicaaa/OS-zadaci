#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUMARGS 20
#define SIZE 100

int main(int argc, char * argv[]) {
	char command[SIZE], *args[NUMARGS];
	int returnStatus, numArgs;

	printf("\nprompt>");
	fflush(stdout);
	
	gets(command);


	numArgs = 0;

	args[numArgs++] = strtok(command, " ");
	while ((args[numArgs++] = strtok(0, " ")) != NULL) {}

	while (strcmp(command, "logout") != 0) {

		if (fork() == 0) {
			sleep(5);
			if (strcmp(args[numArgs-2], "&") == 0) {
				args[numArgs-2] = NULL;
			}
			execvp(args[0], args);
			printf("\nGRESKA PRI IZVRSENJU KOMANDE\n");
			fflush(stdout);
			exit(-1);
		} else {
			if (strcmp(args[numArgs-2], "&") != 0) {

				wait(&returnStatus);
			}
		}
		printf("\nprompt>");
		fflush(stdout);
		
		gets(command);

		numArgs = 0;
		args[numArgs++] = strtok(command, " ");
		while ((args[numArgs++] = strtok(0, " ")) != NULL) {}

	}

	printf("Izasao sam iz programa\n");

	return 0;
}
