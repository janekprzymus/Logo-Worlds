#include "mapa.h"

void write(char plansza[50][50]){
    int i, j;

    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            printf("%2c", plansza[i][j]);
        }
        printf("\n");
    }

}

void save(char plansza[50][50]){
    FILE *fout = fopen("plansza.txt", "w");
    int i, j;

    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            fprintf(fout, "%c", plansza[i][j]);
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

int load(char plansza[50][50]){
    FILE *fin = fopen("plansza.txt", "r");
    if(fin != NULL){
        int i, j;
        char bufor[51];
        for(i=0;i<50;i++){
            fgets(bufor, 52, fin);
            for(j=0;j<50;j++){
                plansza[i][j]=bufor[j];
            }
        }
        fclose(fin);
        return 1;
    }
    else
    {
        fclose(fin);
        return 0;
    }
}