#ifndef LOGIKA_H
#define LOGIKA_H

#include "response.h"
#include "komunikacja.h"
#include "mapa.h"

typedef struct _game{
    current *current_state;
    fields3 *fields_explore;
    map *world;
    //char *token;
} game;

int what_is_x(game *g);
int what_is_y(game *g);
int what_is_x_explore(game *g, int i);
int what_is_y_explore(game *g, int i);
int is_map_ending(game *g);
map *new_segment(game *g);
char mark_current_field(char *field);
char mark_fields_explore(char *field);
void update_fields(map *m);
void map_refine(game *g);
void map_refine_explore(game *g);
game *init_game(char *token);
void reload_map(game *g, char *response);
void reload_map_explore(game *g, char *response);

void do_explore(game *g, char *token);
int do_move(game *g, char *token);
void go_to_the_wall(game *g, char *token);
void along_the_wall(game *g, char *token);
void bot_explore(game *g, char *token);
void bot(game *g, char *token);

#endif