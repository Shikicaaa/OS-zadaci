//Korišćenjem programskog jezika C napisati Linux program koji kreira dva dodatna procesa. Proces
//roditelj i ova dva novokreirana procesa deteta su povezana datavodima u red. Proces roditelj
//prihvata rečenicu po rečenicu koje korisnik unosi sa tastature. Korišćenjem datavoda proces roditelj
//unetu rečenicu prosleđuje prvom procesu detetu. Ovaj proces proverava da li je prvi karakter u
//rečenici veliko slovo i ukoliko nije konvertuje ga u odgovarajuće veliko slovo. Rečenicu zatim,
//koristeći datavod, šalje drugom procesu detetu. Naredni proces proverava da li je poslednji karakter
//u rečenici tačka (.). Ukoliko nije dodaje tačku i rečenicu štampa na standardnom izlazu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
  int pd1[2];
  int pd2[2];
  char linija[80];
  int pid1, pid2;
  if (pipe(pd1) == -1)
  {
    printf("Greska prilikom kreiranja prvog datavoda!\n");
    return -1;
  }
  if (pipe(pd2) == -1)
  {
    printf("Greska prilikom kreiranja drugog datavoda!\n");
    return -1;
  }
  if (pid1 = fork() != 0)
  {
    close(pd1[0]);
    close(pd2[0]);
    close(pd2[1]);
    do
    {
      gets(linija);
      write(pd1[1], linija, strlen(linija)+1);
      printf("Prvi proces poslao u pd1: %s\n", linija);
    }
    while(strcmp(linija, "KRAJ") != 0);
    printf("Prvi proces primio KRAJ\n");
    wait(NULL);
    close(pd1[1]);
    printf("Prvi proces izlazi!\n");
    return 0;
  }
  else if (pid2 = fork() != 0)
  {
    printf("Kreiran drugi proces!\n");
    char linija1[80];
    close(pd1[1]);
    close(pd2[0]);
    do
    {
      read(pd1[0], linija1, 80);
      printf("Drugi proces primio: %s\n", linija1);
      linija1[0] = toupper(linija1[0]);
      write(pd2[1], linija1, strlen(linija1)+1);
      printf("Drugi proces poslao: %s\n", linija1);
    }
    while(strcmp(linija1, "KRAJ") != 0);
    printf("Drugi proces primio KRAJ\n");
    wait(NULL);
    close(pd1[0]);
    close(pd2[1]);
    printf("Drugi proces izlazi!\n");
    exit(0);
  }
  else
  {
    char linija2[80];
    printf("Kreiran treci proces!\n");
    close(pd1[0]);
    close(pd1[1]);
    close(pd2[1]);
    do
    {
      read(pd2[0], linija2, 80);
      printf("Treci proces primio: %s\n", linija2);
      if (linija2[strlen(linija2)-1] != '.')
      {
	       linija2[strlen(linija2)+1] = '\0';
	       linija2[strlen(linija2)] = '.';
      }
      printf("Modifikovana recenica: %s\n", linija2);
    }
    while(strcmp(linija2, "KRAJ.") != 0);
    printf("Treci proces primio KRAJ\n");
    close(pd2[0]);
    printf("Treci proces izlazi!\n");
    exit(0);
  }
}
