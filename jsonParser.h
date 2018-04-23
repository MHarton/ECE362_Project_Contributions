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

typedef struct JsonTable
{
    char **jsonTable;
    int count;
} jtable;


//Auxillary
void print_table(jtable jsonTab);
void print_weather(wdata wda);

//Useful
jtable * split_a_string(char *jsonStr);
int jsonParse(jtable jsonTab, wdata *wdat);
void free_jTable(jtable *jsonTab);
void clean_Weather(wdata * wda);
void free_Weather(wdata* wda);

#endif
