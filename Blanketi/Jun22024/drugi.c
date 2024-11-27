#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    char reci[255] = {};
    int pd1[2];
    int pd2[2];
    pipe(pd1);
    pipe(pd2);
    
    if(fork() != 0){
        close(pd1[0]);
        close(pd2[1]);
        close(pd2[0]);
        for(int i = 1;i < argc;i++){
            strcat(reci,argv[i]);
            strcat(reci, " ");
        }
        write(pd1[1],reci,255);
        close(pd1[1]);
        wait(NULL);
    }
    else{
        if(fork() != 0){
            printf("Incijalizacija drugog procesa!\n");
            close(pd1[1]);
            close(pd2[0]);
            char buffer[255];
            read(pd1[0],buffer,255);
            int br = 0;
            char* reci[50];
            reci[br++] = strtok(buffer, " ");
            while((reci[br++] = strtok(NULL, " ")) != NULL){
            }
            char* nazivfajla = reci[0];
            FILE * f = fopen(nazivfajla, "r");
            int brojLinije = 1;
            char line[255];
            while(!feof(f) && fgets(line,255,f) != NULL){
                //mora da proveri da li ima sta da procita.
                for(int i = 1;i<br-1;i++){
                    if(strstr(line, reci[i])){
                        printf("Pronadjenja je kljucna rec \"%s\"\n",reci[i]);
                        write(pd2[1],&brojLinije,sizeof(int));
                        break;
                    }
                }
                brojLinije++;
            }
            brojLinije = -69;
            write(pd2[1],&brojLinije,sizeof(int));
            close(pd2[1]);
            close(pd1[0]); 
            fclose(f);
            wait(NULL);
        }
        else{
            printf("Inicijalizacija treceg procesa!\n");
            close(pd1[0]);
            close(pd1[1]);
            close(pd2[1]);
            int c = 0;
            int buff;
            int provera;
            while(provera = read(pd2[0],&buff,sizeof(int))){
                if(provera == 0) {
                    break;
                }
                if(buff == -69)
                    break;
                c += buff;
            }
            printf("Ovde je suma svih strana koje sadrze kljucne reci: %d\n",c);
            close(pd2[0]);
        }
    }
}