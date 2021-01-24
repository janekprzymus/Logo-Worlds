#ifndef RESPONSE_H
#define RESPONSE_H

#include "def.h"

typedef struct _fields3
{
    int x[3];
    int y[3];
    char *type[3];
}   fields3;

typedef struct _current
{
    int x;
    int y;
    char *type;
    char *direction;
}   current;

current *read_response(char *response);
fields3 *read_response_explore(char *response);
void free_game_state(current *g);
void free_game_state_explore(fields3 *g);

#endif