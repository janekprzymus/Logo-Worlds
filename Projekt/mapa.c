#include "mapa.h"

void wypisz(char plansza[50][50]){
    int i, j;

    for(i=0;i<50;i++){
        for(j=0;j<50;j++){
            printf("%2c",plansza[i][j]);
        }
        printf("\n");
    }

}

void zapisz(char plansza[50][50]){
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

int wczytaj(char plansza[50][50]){
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

void mark_current(char plansza[50][50], char *token){
    int i, j;
    char *response = info(token);
    current *field = dzejson_current(response);
    free(response);
    for(i=0; i<50; i++){
        for(j=0; j<50; j++){
            if(plansza[i][j]=='g')
                plansza[i][j]='G';
            if(plansza[i][j]=='s')
                plansza[i][j]='S';
            if(plansza[i][j]=='w')
                plansza[i][j]='W';
        }
    }

    if(strcmp(field->type, "grass")==0)
        plansza[MAX-field->y][field->x]='g';
    if(strcmp(field->type, "sand")==0)
        plansza[MAX-field->y][field->x]='s';
    if(strcmp(field->type, "wall")==0)
        plansza[MAX-field->y][field->x]='w';
    free(field->type);
    free(field->direction);
    free(field);
}