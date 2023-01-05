#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <log.h>
#include "map.h"



int map_init(map *my_map) {
    my_map->size = 0;
}

int map_find(char *key, map my_map) {
    for (int i = 0; i < my_map.size; i++) {
        if (strcmp(((my_map.array)[i]).key, key) == 0) {
            return i;
        }
    }
    return -1;
}

void map_insert(char *key, int value, map *my_map) {
    int pos = map_find(key, *my_map);
    map_token new_token;
    new_token.key = key;
    new_token.value = value; 
    if (pos == -1) {
        my_map->array[my_map->size] = new_token;
        my_map->size++;
    } else {
        my_map->array[pos] = new_token;
    }
}

void map_print(map my_map) {
    printf("[ ");
    for (int i = 0; i < my_map.size; i++) {
        printf("{%s : %d} ", my_map.array[i].key, my_map.array[i].value);
    }
    printf("]\n");
}


// int main() {
//     map my_map;
//     map_init(&my_map);

//     // my_map.array[0].key = "abc";
//     // my_map.array[0].value = 15;
//     // my_map.size++;
//     map_insert("abc", 5, &my_map);
//     map_print(my_map);
//     printf("find res: %d\n", map_find("abd", my_map));
//     printf("find res: %d\n", map_find("abc", my_map));
//     map_insert("xyz", 63, &my_map);
//     printf("find res: %d\n", map_find("abc", my_map));
//     printf("find res: %d\n", map_find("xyz", my_map));
//     map_print(my_map);
//     map_insert("xyz", 22, &my_map);
//     map_print(my_map);
    
// }