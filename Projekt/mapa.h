#ifndef MAPA_H
#define MAPA_H

#include "response.h"
#include "komunikacja.h"

void write(char plansza[50][50]);
void save(char plansza[50][50]);
int load(char plansza[50][50]);
void mark_current(char plansza[50][50], char *token, int to_do);
void show_fields(char plansza[50][50], char *token);

#endif