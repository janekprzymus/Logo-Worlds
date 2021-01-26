#include "logika.h"

int what_is_x(game *g){
    int x = (g->current_state->x) - (g->world->x_start) + (g->world->p);
    return x;
}

int what_is_y(game *g){
    int y = (g->current_state->y) - (g->world->y_start) + (g->world->q);
    return y;
}

int what_is_x_explore(game *g, int i){
    int x = (g->fields_explore->x[i]) - (g->world->x_start) + (g->world->p);
    return x;
}

int what_is_y_explore(game *g, int i){
    int y = (g->fields_explore->y[i]) - (g->world->y_start) + (g->world->q);
    return y;
}

int is_map_ending(game *g){
    if(what_is_x(g)==0 || what_is_y(g)==0 || what_is_x(g)==g->world->kolumny-1 || what_is_y(g)==g->world->wiersze-1)
        return 1;
    else
        return 0;
}

map *new_segment(game *g){
    if(what_is_x(g)==0){
        g->world = new_segment_west(g->world);
        return g->world;
    } else if(what_is_y(g)==0){
        g->world = new_segment_south(g->world);
        return g->world;
    } else if(what_is_x(g)==g->world->kolumny-1){
        g->world = new_segment_east(g->world);
        return g->world;
    } else if(what_is_y(g)==g->world->wiersze-1){
        g->world = new_segment_north(g->world);
        return g->world;
    }
}

char mark_current_field(char *field){
    if(strcmp(field, "grass")==0)
        return 'g';
    else if(strcmp(field, "sand")==0)
        return 's';
    else if(strcmp(field, "wall")==0)
        return 'w';
}

char mark_fields_explore(char *field){
    if(strcmp(field, "grass")==0)
        return 'G';
    else if(strcmp(field, "sand")==0)
        return 'S';
    else if(strcmp(field, "wall")==0)
        return 'W';
}

void update_fields(map *m){
    for(int i=0; i<m->wiersze-1; i++){
        for(int j=0; j<m->kolumny-1; j++){
            if(m->plansza[i][j]=='g')
                m->plansza[i][j]='G';
            if(m->plansza[i][j]=='s')
                m->plansza[i][j]='S';
            if(m->plansza[i][j]=='w')
                m->plansza[i][j]='W';
        }
    }
}

void map_refine(game *g){
    if(is_map_ending(g)==1){
        g->world = new_segment(g);
    }
    g->world->plansza[what_is_y(g)][what_is_x(g)] = mark_current_field(g->current_state->type); 
}

void map_refine_explore(game *g){
    for(int i=0; i<3; i++)
        g->world->plansza[what_is_y_explore(g,i)][what_is_x_explore(g,i)] = mark_fields_explore(g->fields_explore->type[i]);
}


game *init_game(char *token){
    game *gra = (game*) malloc(sizeof(game));
    gra->world = map_init(gra->world);
    write(gra->world);

    char *response;
    response = info(token);
    gra->current_state = read_response(response);
    free(response);

    gra->world->x_start = gra->current_state->x;
    gra->world->y_start = gra->current_state->y;

    map_refine(gra);
    write(gra->world);
    save(gra->world);
    draw_map(gra->world);

    return gra;
}

void reload_map(game *g, char *response){
    free_game_state(g->current_state);
    //g->world=wczytaj();
    g->current_state = read_response(response);
    free(response);

    update_fields(g->world);
    map_refine(g);

    write(g->world);
    save(g->world);
    draw_map(g->world);
}

void reload_map_explore(game *g, char *response){
    if(g->fields_explore!=NULL)
        free_game_state_explore(g->fields_explore);
    //g->world=wczytaj();
    g->fields_explore = read_response_explore(response);
    free(response);

    map_refine_explore(g);

    write(g->world);
    save(g->world);
    draw_map(g->world);
}

void do_explore(game *g, char *token){
    char *response;
    response = explore(token);
    reload_map_explore(g, response);
}

int do_move(game *g, char *token){
    int x = g->current_state->x;
    int y = g->current_state->y;
    
    char *response;
    response = move(token);
    reload_map(g, response);

    if(strcmp(g->current_state->direction, "W")==0){
        if(x == g->current_state->x){
            g->world->plansza[what_is_y(g)][what_is_x(g)-1]='W';
            write(g->world);
            save(g->world);
            draw_map(g->world);
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(strcmp(g->current_state->direction, "E")==0){
        if(x == g->current_state->x){
            g->world->plansza[what_is_y(g)][what_is_x(g)+1]='W';
            write(g->world);
            save(g->world);
            draw_map(g->world);
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(strcmp(g->current_state->direction, "N")==0){
        if(y == g->current_state->y){
            g->world->plansza[what_is_y(g)+1][what_is_x(g)]='W';
            write(g->world);
            save(g->world);
            draw_map(g->world);
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(strcmp(g->current_state->direction, "S")==0){
        if(y == g->current_state->y){
            g->world->plansza[what_is_y(g)-1][what_is_x(g)]='W';
            write(g->world);
            save(g->world);
            draw_map(g->world);
            return 1;
        }
        else{
            return 0;
        }
    }
}

void go_to_the_wall(game *g, char *token){
    do_explore(g, token);
    while(do_move(g, token)!=1)
        do_explore(g, token);

    char *response;
    response = rotate(token, "right");
    reload_map(g, response);
}

void along_the_wall(game *g, char *token){
    do_explore(g, token);

    if(strcmp(g->current_state->direction, "W")==0){
        while(do_move(g,token)!=1 && (g->world->plansza[what_is_y(g)-1][what_is_x(g)]=='W')){
            do_explore(g,token);
        }
    }   
    if(strcmp(g->current_state->direction, "E")==0){
        while(do_move(g,token)!=1 && (g->world->plansza[what_is_y(g)+1][what_is_x(g)]=='W')){
            do_explore(g,token);
        }
    }    
    if(strcmp(g->current_state->direction, "N")==0){
        while(do_move(g,token)!=1 && (g->world->plansza[what_is_y(g)][what_is_x(g)-1]=='W')){
            do_explore(g,token);
        }
    } 
    if(strcmp(g->current_state->direction, "S")==0){
        while(do_move(g,token)!=1 && (g->world->plansza[what_is_y(g)][what_is_x(g)+1]=='W')){
            do_explore(g,token);
        }
    }
}

void bot_explore(game *g, char *token){
    int a=0;
    int x = g->current_state->x;
    int y = g->current_state->y;
    do_move(g, token);

    while(g->current_state->x != g->world->x_start || g->current_state->y != g->world->y_start){
        along_the_wall(g, token);
        if(strcmp(g->current_state->direction, "E")==0){
            if(g->world->plansza[what_is_y(g)+1][what_is_x(g)]!='W'){
                char *response;
                response = rotate(token, "left");
                reload_map(g, response);
                a--;
            }
            else
            {
                char *response;
                response = rotate(token, "right");
                reload_map(g, response);
                a++;
            }
        }
        else if(strcmp(g->current_state->direction, "W")==0){
            if(g->world->plansza[what_is_y(g)-1][what_is_x(g)]!='W'){
                char *response;
                response = rotate(token, "left");
                reload_map(g, response);
                a--;
            }
            else
            {
                char *response;
                response = rotate(token, "right");
                reload_map(g, response);
                a++; 
            }
        }
        else if(strcmp(g->current_state->direction, "N")==0){
            if(g->world->plansza[what_is_y(g)][what_is_x(g)-1]!='W'){
                char *response;
                response = rotate(token, "left");
                reload_map(g, response);
                a--;
            }
            else
            {
                char *response;
                response = rotate(token, "right");
                reload_map(g, response);
                a++; 
            }
        }
        else if(strcmp(g->current_state->direction, "S")==0){
            if(g->world->plansza[what_is_y(g)][what_is_x(g)+1]!='W'){
                char *response;
                response = rotate(token, "left");
                reload_map(g, response);
                a--;
            }
            else
            {
                char *response;
                response = rotate(token, "right");
                reload_map(g, response);
                a++; 
            }
        }
    }
}

void bot(game *g, char *token){
    go_to_the_wall(g, token);
    bot_explore(g, token);
}