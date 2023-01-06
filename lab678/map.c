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

//     while (1) {
//         int f;
//         scanf("%d", &f);
//         map_print(my_map);
//         char key[100];
//         int val;
//         if (f == 1) {
//             scanf("%s", key);
//             scanf("%d", &val);
//             printf("( %s : %d )\n", key, val);
//             map_insert(key, val, &my_map);
//         } else {
//             scanf("%s", key);
//             printf("( %s )\n", key);
//             printf("%d\n", map_find(key, my_map));
//         }
//         map_print(my_map);
        
//     }
    
// }