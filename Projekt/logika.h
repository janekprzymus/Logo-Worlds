#ifndef LOGIKA_H
#define LOGIKA_H

#include "response.h"
#include "komunikacja.h"

/*typedef struct _game{
    current *current_state;
    fields3 *fields_explore;
    map *world;
} game;*/

void mark_current(char plansza[50][50], char *token, int to_do);
void show_fields(char plansza[50][50], char *token);

#endif