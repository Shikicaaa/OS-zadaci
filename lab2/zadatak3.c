#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define NUMARGS 20
#define SIZE 100
#define KRAJ 42

void * obrada(void * command) {
	char * args[NUMARGS];
	int returnStatus, numArgs;

	printf("\nprompt>");
	fflush(stdout);

	numArgs = 0;

	args[numArgs++] = strtok(command, " ");
	while ((args[numArgs++] = strtok(0, " ")) != NULL) {}

	if (strcmp(command, "logout") != 0) {

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
		
	} else { return KRAJ; }

	printf("Izasao sam iz programa\n");

	return 0;
}

int main(int argc, char * argv[]) {
	char command[SIZE];
	int ret;
	pthread_t nit;
	do {
		printf("\nprompt>");

		gets(command);

		pthread_create(&nit, NULL, (void*) obrada, (void*) command);

		pthread_join(nit,&ret);

	}
	while(ret == 0);
	return 0;
}
