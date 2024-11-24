#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char* argv[]){
    double s = 0.0;
    for(int i = 0;i<argc;i++){
        printf("%s ", argv[i]);
        s += atof(argv[i]);
    }
    double prosek = s / (double)(argc-1);
    printf("\nProsek sume je: %f\n a zbir je %f\n a ima %d elemenata\n", prosek,s,argc-1);
    return 0;
}