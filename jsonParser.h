#ifndef PARSER
#define PARSER
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct WeatherData
{
    char weather[50];
    char temp[50];
} wdata;

int jsonParse(char *jsonStr);



#endif
