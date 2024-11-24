#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

int main(int argc, char * argv[]) {
	printf("%s\n", argv[0]);

	int fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0777);
	dup2(fd, 1);
	close(fd);
	execlp(argv[1], argv[1], NULL);
	printf("Ne bi trebalo nikad se izvrsi\n");

	return 0;
}
