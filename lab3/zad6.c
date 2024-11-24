#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define MUTEX_KEY 10101
#define PROC_A_KEY 10102
#define PROC_B_KEY 10103

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};

int main () {
	int mutexID, procaID, procbID, retCode;

	union semun semopts;
	char linija[100];
	FILE* fileA, *fileB, *fileC;

	struct sembuf sem_lock = {0, -1, 0};
	struct sembuf sem_unlock = {0, -1, 0};

	mutexID = semget((key_t)MUTEX_KEY, 1, 0666 | IPC_CREAT);
	procaID = semget((key_t)PROC_A_KEY, 1, 0666 | IPC_CREAT);
	procbID = semget((key_t)PROC_B_KEY, 1, 0666 | IPC_CREAT);

	semopts.val = 1;
	semctl(mutexID, 0, SETVAL, semopts);
	semopts.val = 1;
	semctl(mutexID, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(mutexID, 0, SETVAL, semopts);

	if (fork() == 0) {
		mutexID = semget((key_t)MUTEX_KEY, 1, 0666);
		procaID = semget((key_t)PROC_A_KEY, 1, 0666);
		procbID = semget((key_t)PROC_B_KEY, 1, 0666);

		fileA = fopen("prva.txt", "r");

		while (!feof(fileA)) {
			fgets(linija, 100, fileA);
			semop(procaID, &sem_lock, 1);
			semop(mutexID, &sem_lock, 1);

			fileC = fopen("zbir.txt", "a");

			fprintf(fileC, "%s\n", linija);
			fclose(fileC);
			semop(mutexID, &sem_unlock, 1);
			semop(procbID, &sem_unlock, 1);
		}
		fclose(fileA);
		exit(0);
	
	} else {
		mutexID = semget((key_t)MUTEX_KEY, 1, 0666);
		procaID = semget((key_t)PROC_A_KEY, 1, 0666);
		procbID = semget((key_t)PROC_B_KEY, 1, 0666);

		fileB = fopen("druga.txt", "r");

		while (!feof(fileB)) {
			fgets(linija, 100, fileB);
			semop(procbID, &sem_lock, 1);
			semop(mutexID, &sem_lock, 1);

			fileC = fopen("zbir.txt", "a");

			fprintf(fileC, "%s\n", linija);
			fclose(fileC);
			semop(mutexID, &sem_unlock, 1);
			semop(procaID, &sem_unlock, 1);
		}
		fclose(fileB);
		wait(2);
		semctl(mutexID, 0, IPC_RMID, 0);
		semctl(procaID, 0, IPC_RMID, 0);
		semctl(procbID, 0, IPC_RMID, 0);
		exit(0);
	}

	return 0;
}

