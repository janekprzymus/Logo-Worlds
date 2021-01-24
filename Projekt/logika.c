#include "logika.h"

void mark_current(char plansza[50][50], char *token, int to_do){
    int i, j;
    char *response;
    if(to_do==0){
        response = info(token);
    }
    if(to_do==1){
        response = move(token);
    }
    if(to_do==21){
        response = rotate(token, "left");
    }
    if(to_do==22){
        response = rotate(token, "right");
    }
    if(to_do==4){
        response = reset(token);
    }

    current *field = read_response(response);
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
    
    free_game_state(field);
}

void show_fields(char plansza[50][50], char *token){
    int i;
    char *response;
    response=explore(token);
    fields3 *polee = read_response_explore(response);
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
    
    free_game_state_explore(polee);
}