#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../../cJSON/cJSON.h"

#define MAX 49

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

#endif