#include "logika.h"

int main(int argc, char **argv)
{
    char *token;
    char *s1="M";
    char *s21="Rleft";
    char *s22="Rright";
    char *s3="E";
    char *s4="reset";
    char *s5="info";
    token=argv[1];
    int i, j;
    game *gra;

    if(argc>2){
        if(strcmp(argv[2], "play")==0){
            char *response;
            response = reset(token);
            gra = init_game(token);
            free(response);
            while(1){
                char komenda[10];
                printf("Podaj komendę: (M-move, Rleft - obróć w lewo, Rright - obróć w prawo, E - eksploruj, reset, info, end - zakończ grę)\n");
                scanf("%s", komenda);
                if(strcmp(komenda,s5)==0){
                    char *response;
                    response = info(token);
                    reload_map(gra, response);
                    printf("Aktualne współrzędne lokalne czołgu: x=%d, y=%d\n", what_is_x(gra)+1, what_is_y(gra)+1);
                    printf("Kierunek czołgu: %s\n", gra->current_state->direction);
                }
                if(strcmp(komenda,s1)==0){
                    do_move(gra, token);
                    printf("Aktualne współrzędne lokalne czołgu: x=%d, y=%d\n", what_is_x(gra)+1, what_is_y(gra)+1);
                    printf("Kierunek czołgu: %s\n", gra->current_state->direction);
                }
                else if(strcmp(komenda,s21)==0){
                    char *response;
                    response = rotate(token, "left");
                    reload_map(gra, response);
                    printf("Aktualne współrzędne lokalne czołgu: x=%d, y=%d\n", what_is_x(gra)+1, what_is_y(gra)+1);
                    printf("Kierunek czołgu: %s\n", gra->current_state->direction);
                }
                else if(strcmp(komenda,s22)==0){
                    char *response;
                    response = rotate(token, "right");
                    reload_map(gra, response);
                    printf("Aktualne współrzędne lokalne czołgu: x=%d, y=%d\n", what_is_x(gra)+1, what_is_y(gra)+1);
                    printf("Kierunek czołgu: %s\n", gra->current_state->direction);
                }
                else if(strcmp(komenda,s3)==0){
                    do_explore(gra, token);
                    printf("Aktualne współrzędne lokalne czołgu: x=%d, y=%d\n", what_is_x(gra)+1, what_is_y(gra)+1);
                    printf("Kierunek czołgu: %s\n", gra->current_state->direction);
                }
                else if(strcmp(komenda,s4)==0){
                    char *response;
                    response = reset(token);
                    gra = init_game(token);
                    free(response);
                }
                else if(strcmp(komenda,"end")==0)
                    break;
                else
                {
                    printf("\nBłąd: nieznana komenda!\n");
                    exit(-1);
                }
            }
        }
        else if(strcmp(argv[2], "reset")==0){
            char *response;
            response = reset(token);
            free(response);
            return 0;
        }
        else if(strcmp(argv[2], "bot")==0){
            char *response;
            response = reset(token);
            gra = init_game(token);
            free(response);
            bot(gra, token);
        }
    }
    else
    {
        gra = init_game(token);
        printf("Aktualne współrzędne lokalne czołgu: x=%d, y=%d\n", what_is_x(gra)+1, what_is_y(gra)+1);
        printf("Kierunek czołgu: %s\n", gra->current_state->direction);
    }
    
    free_map(gra->world);
    //free(gra->token);
    free_game_state(gra->current_state);
    if(gra->fields_explore!=NULL)
        free_game_state_explore(gra->fields_explore);
    free(gra);

    return 0;
}
