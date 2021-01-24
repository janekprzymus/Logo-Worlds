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
    
    if(load(plansza)==0)
    {
        for(i=0;i<50;i++){
            for(j=0;j<50;j++){
                plansza[i][j]='.';
            }
        }
    }
    

    if(argc<3){
        mark_current(plansza, token, 0);
        write(plansza);
    }
    else
    {
        for(int k=2;k<argc;k++){
            if(strcmp(argv[k],s1)==0){
                mark_current(plansza, token, 1);
            }
            else if(strcmp(argv[k],s21)==0){
                char *response;
                response=rotate(token,"left");
                free(response);
                mark_current(plansza, token, 0);
            }
            else if(strcmp(argv[k],s22)==0){
                char *response;
                response=rotate(token,"right");
                free(response);
                mark_current(plansza, token, 0);
            }
            else if(strcmp(argv[k],s3)==0){
                show_fields(plansza, token);
            }
            else if(strcmp(argv[k],s4)==0){
                for(i=0;i<50;i++){
                    for(j=0;j<50;j++){
                        plansza[i][j]='.';
                    }
                }
                mark_current(plansza, token, 4);
            }
            else
            {
                printf("\nBłąd: nieznana komenda!\n");
                exit(-1);
            }
            write(plansza);
        }
    }
    
    save(plansza);
    return 0;
}