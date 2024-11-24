#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define NUMARGS 20
#define SIZE 100
#define KRAJ 42

int obrada(char * command) {
	char *args[NUMARGS];
	int returnStatus, numArgs;

	printf("Usao sam u obradu\n");

	numArgs = 0;

	printf("%s\n", command);

	args[numArgs++] = strtok(command, " \n");
	while ((args[numArgs++] = strtok(0, " \n")) != NULL) {}

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
				return 0;
			}
		}
		printf("\nprompt>");
		fflush(stdout);

	}

	printf("Izasao sam iz programa\n");

	return KRAJ;
}

int obrada_bat(char * pathToBatchFile) {
	FILE* f;
	char command[SIZE];
	int ret = 0;

	printf("usao sam u obrada_bat\n");

	f = fopen(pathToBatchFile, "r");

	if (!f) {
		printf("Nije dobro prosledjen batch file\n");
		return -1;
	}

	fgets(command, SIZE, f);

	while(!feof(f)) {

		ret = obrada(command);

		if (ret == KRAJ) {
			break;
		}

		fgets(command, SIZE, f);
	}

	return ret;
}

int main(int argc, char * argv[]) {
	char command[SIZE];
	int ret = 0;

	
	do {
		printf("\nprompt>");
	
		gets(command);

		if (command[0] == '@') {
			char * batch = strtok(command + 1, " ");
			ret = obrada_bat(batch);
		}
	}
	while (ret == 0);
	return 0;

}
