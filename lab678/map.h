#ifndef MAP
#define MAP

#include <stdio.h>
#define MAP_MAX_SIZE 1000


typedef struct _map_token {
    char *key;
    int value;
} map_token;

typedef struct _map{
    map_token array[MAP_MAX_SIZE];
    int size;
} map;


int map_init(map *my_map);

int map_find(char *key, map my_map);

void map_print(map my_map);

#endif