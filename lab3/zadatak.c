#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define MUTEX_KEY 10101
#define PROC_A_KEY 10102
#define PROC_B_KEY 10103
#define DUZINA 80

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main()
{
	int mutexid, procaid, procbid, retCode;
	union semun semopts;
	int broj;
	FILE* file;

	struct sembuf sem_lock = {0, -1, 0};
	struct sembuf sem_unlock = {0, 1, 0};

	mutexid = semget((key_t)MUTEX_KEY, 1, 0666 | IPC_CREAT);
	procaid = semget((key_t)PROC_A_KEY, 1, 0666 | IPC_CREAT);
	procbid = semget((key_t)PROC_B_KEY, 1, 0666 | IPC_CREAT);


	semopts.val = 1;
	semctl(mutexid, 0, SETVAL, semopts);
	semopts.val = 1;
	semctl(procaid, 0, SETVAL, semopts);
	semopts.val = 0;
	semctl(procbid, 0, SETVAL, semopts);

	if (fork() == 0)
	{
		mutexid = semget((key_t)MUTEX_KEY, 1, 0666);
		procaid = semget((key_t)PROC_A_KEY, 1, 0666);
		procbid = semget((key_t)PROC_B_KEY, 1, 0666);
	
		semop(procaid, &sem_lock, 1);
		semop(mutexid, &sem_lock, 1);

		file = fopen("brojevi.bat", "a");

		for (int i = 0; i < 3; i++) {
			broj = rand() % RAND_MAX;	
fprintf(file, "%s", broj);
		}

		fclose(file);


		semop(mutexid, &sem_unlock, 1);
		semop(procbid, &sem_unlock, 1);

		exit(0);
	}
	else
	{
		mutexid = semget((key_t)MUTEX_KEY, 1, 0666);
		procaid = semget((key_t)PROC_A_KEY, 1, 0666);
		procbid = semget((key_t)PROC_B_KEY, 1, 0666);


		semop(procbid, &sem_lock, 1);
		semop(mutexid, &sem_lock, 1);
		file = fopen("brojevi.bat", "a");
		broj = rand() % RAND_MAX;
		fprintf(file, "%s", broj);
		fclose(file);
		semop(mutexid, &sem_unlock, 1);
		semop(procaid, &sem_unlock, 1);


		wait(NULL);
		semctl(mutexid, 0, IPC_RMID, 0);
		semctl(procaid, 0, IPC_RMID, 0);
		semctl(procbid, 0, IPC_RMID, 0);
	}
}
