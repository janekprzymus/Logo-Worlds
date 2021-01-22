#include "mapa.h"

int main(int argc, char **argv)
{
    /* Program obługuje się poprzez podanie tokena świata jako pierwszy argument linii komend.
    Następnie jeśli nie ma kolejnych argumentow - program wyświetla informacje o świecie.
    Jeśli następne argumenty występują, w zaleznosci od nich program wykonuje dane polecenia:
    ("M" - ruch, "Rleft" - obrot w lewo, "Rright" - obrot w prawo, "E" - eksploracja) */ 
    char *url;
    char *token;
    char *s1="M";
    char *s21="Rleft";
    char *s22="Rright";
    char *s3="E";
    char *s4="reset";
    token=argv[1];
    char plansza[50][50];
    int i, j;
    
    if(wczytaj(plansza)==0)
    {
        for(i=0;i<50;i++){
            for(j=0;j<50;j++){
                plansza[i][j]='.';
            }
        }
    }
    

    if(argc<3){
        char *response;
        response=info(token);
        free(response);
        wypisz(plansza);
    }
    else
    {
        for(int k=2;k<argc;k++){
            char *response;
            if(strcmp(argv[k],s1)==0){
                response=move(token);
                pole *field = dzejson(response);
                free(response);
                printf("x: %d\n",field->x);
                printf("y: %d\n",field->y);
                printf("Typ pola: %s\n",field->type);
                if(strcmp(field->type, "grass")==0)
                    plansza[MAX-field->y][field->x]='G';
                if(strcmp(field->type, "sand")==0)
                    plansza[MAX-field->y][field->x]='S';
                if(strcmp(field->type, "wall")==0)
                    plansza[MAX-field->y][field->x]='W';

                free(field->type);
                free(field);
            }
            else if(strcmp(argv[k],s21)==0){
                response=rotate(token,"left");
                free(response);
            }
            else if(strcmp(argv[k],s22)==0){
                response=rotate(token,"right");
                free(response);
            }
            else if(strcmp(argv[k],s3)==0){
                response=explore(token);
                pole3 *polee = dzejson_explore(response);
                free(response);
                for(i=0; i<3; i++){
                    printf("x_%d: %d\n", i, polee->x[i]);
                    printf("y_%d: %d\n", i, polee->y[i]);
                    printf("Typ pola %d: %s\n", i, polee->type[i]);
                    if(strcmp(polee->type[i], "grass")==0)
                        plansza[MAX-polee->y[i]][polee->x[i]]='G';
                    if(strcmp(polee->type[i], "sand")==0)
                        plansza[MAX-polee->y[i]][polee->x[i]]='S';
                    if(strcmp(polee->type[i], "wall")==0)
                        plansza[MAX-polee->y[i]][polee->x[i]]='W';
                }
                for(i=0; i<3; i++){
                free(polee->type[i]);
                }
                free(polee);
            }
            else if(strcmp(argv[k],s4)==0){
                for(i=0;i<50;i++){
                    for(j=0;j<50;j++){
                        plansza[i][j]='.';
                    }
                }
                response=reset(token);
                pole *field = dzejson(response);
                free(response);
                printf("x: %d\n",field->x);
                printf("y: %d\n",field->y);
                printf("Typ pola: %s\n",field->type);
                if(strcmp(field->type, "grass")==0)
                    plansza[MAX-field->y][field->x]='G';
                if(strcmp(field->type, "sand")==0)
                    plansza[MAX-field->y][field->x]='S';
                if(strcmp(field->type, "wall")==0)
                    plansza[MAX-field->y][field->x]='W';

                free(field->type);
                free(field);
            }
            else
            {
                printf("\nBłąd: nieznana komenda!\n");
                exit(-1);
            }
            mark_current(plansza, token);
            wypisz(plansza);
        }
    }
    
    zapisz(plansza);
    return 0;
}