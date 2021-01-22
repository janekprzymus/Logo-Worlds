#include "komunikacja.h"
#include "response.h"
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
        int i;
        for(i=2;i<argc;i++){
            char *response;
            if(strcmp(argv[i],s1)==0){
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
            else if(strcmp(argv[i],s21)==0){
                response=rotate(token,"left");
                free(response);
            }
            else if(strcmp(argv[i],s22)==0){
                response=rotate(token,"right");
                free(response);
            }
            else if(strcmp(argv[i],s3)==0){
                response=explore(token);
                pole3 *polee = dzejson_explore(response);
                free(response);
                printf("x_0: %d\n",polee->x[0]);
                printf("y_0: %d\n",polee->y[0]);
                printf("Typ pola 0: %s\n",polee->type[0]);
                printf("x_1: %d\n",polee->x[1]);
                printf("y_1: %d\n",polee->y[1]);
                printf("Typ pola 1: %s\n",polee->type[1]);
                printf("x_2: %d\n",polee->x[2]);
                printf("y_2: %d\n",polee->y[2]);
                printf("Typ pola 2: %s\n",polee->type[2]);
                if(strcmp(polee->type[0], "grass")==0)
                    plansza[MAX-polee->y[0]][polee->x[0]]='G';
                if(strcmp(polee->type[1], "grass")==0)
                    plansza[MAX-polee->y[1]][polee->x[1]]='G';
                if(strcmp(polee->type[2], "grass")==0)
                    plansza[MAX-polee->y[2]][polee->x[2]]='G';
                if(strcmp(polee->type[0], "sand")==0)
                    plansza[MAX-polee->y[0]][polee->x[0]]='S';
                if(strcmp(polee->type[1], "sand")==0)
                    plansza[MAX-polee->y[1]][polee->x[1]]='S';
                if(strcmp(polee->type[2], "sand")==0)
                    plansza[MAX-polee->y[2]][polee->x[2]]='S';
                if(strcmp(polee->type[0], "wall")==0)
                    plansza[MAX-polee->y[0]][polee->x[0]]='W';
                if(strcmp(polee->type[1], "wall")==0)
                    plansza[MAX-polee->y[1]][polee->x[1]]='W';
                if(strcmp(polee->type[2], "wall")==0)
                    plansza[MAX-polee->y[2]][polee->x[2]]='W';

                for(int i=0;i<3;i++){
                free(polee->type[i]);
                }
                free(polee);
            }
            else if(strcmp(argv[i],s4)==0){
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
            wypisz(plansza);
        }
    }
    
    zapisz(plansza);
    return 0;
}