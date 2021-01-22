#ifndef MAPA_H
#define MAPA_H

#include "response.h"
#include "komunikacja.h"

void wypisz(char plansza[50][50]);
void zapisz(char plansza[50][50]);
int wczytaj(char plansza[50][50]);
void mark_current(char plansza[50][50], char *token);

#endif