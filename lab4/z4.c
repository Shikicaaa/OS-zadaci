#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int pd[2];

	if (pipe(pd) < 0) {
		printf("Nije uspelo inicijalizacija datavoda\n");
		return -1;
	}

	if (fork() == 0) {
		char* args[20];

		close(1);
		dup(pd[1]);
		close(pd[1]);
		close(pd[0]);

		for (int i = 1; i < argc; i++) {
			args[i-1] = argv[i];
		}
		args[argc-1] = NULL;

		execv(args[0], args);
	} else {
		close(0);
		dup(pd[0]);

		close(pd[1]);
		close(pd[0]);

		execlp("more", "more", NULL);
	}

	return 0;
}
