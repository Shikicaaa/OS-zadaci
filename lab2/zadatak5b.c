#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char * argv[]) {
	char * args[4];
	char buf[100];
	gets(buf);

	if (fork() == 0) {
		args[0] = (char*)malloc(100 * sizeof(char));
		strcpy(args[0], "cp");
		
		args[1] = (char*)malloc(100 * sizeof(char));
		strcpy(args[1], buf); 
		args[2] = (char*)malloc(100 * sizeof(char));
		strcpy(args[2], "./tmp");

		args[3] = NULL;

		if (execvp("cp", args) < 0) {
			printf("NE RADI");
			exit(1);
		}

	} else {
		wait(NULL);
	}
	return 0;
}
