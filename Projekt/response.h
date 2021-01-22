#ifndef RESPONSE_H
#define RESPONSE_H

#include "def.h"

typedef struct _pole
{
    int x;
    int y;
    char *type;
} pole;

typedef struct _pole3
{
    int x[3];
    int y[3];
    char *type[3];
}   pole3;

pole *dzejson(char *response);
pole3 *dzejson_explore(char *response);

#endif