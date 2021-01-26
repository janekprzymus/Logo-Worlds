#ifndef PPNG_H
#define PPNG_H

#include "mapa.h"
#include <png.h>

void read_png_file(char *filename, int *width, int *height, png_byte *color_type, png_byte *bit_depth, png_bytep **row_pointers);
void write_png_file(char *filename, int width, int height, png_byte color_type, png_byte bit_depth, png_bytep *row_pointers);
void process_png_file(int width, int height, png_bytep *row_pointers);
png_bytep * create_image(int width, int height);
void init_png_file(int width, int height, png_bytep *row_pointers);
void copy_tile(int xs, int ys, int width, int height, png_bytep *row_pointers, png_bytep *row_pointers_from, int idx);
void draw_map(map *m);

#endif