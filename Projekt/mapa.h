#ifndef MAPA_H
#define MAPA_H

#include "def.h"

#define N 5

typedef struct _map{
    char **plansza;
    int wiersze, kolumny, p, q;
    int x_start, y_start;
} map;

void write(map *m);
void save(map *m);

void alloc_map_memory(map *m, int wiersze, int kolumny);
map *map_init(map *m);
void move_map(map *new, map *m, int dx, int dy);
void free_map(map *m);
map *new_segment_north(map *m);
map *new_segment_south(map *m);
map *new_segment_west(map *m);
map *new_segment_east(map *m);

#endif