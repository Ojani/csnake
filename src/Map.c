#include "../include/Map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_map(struct Map* map) {
  printf("\ec");

  for (int i = 0; i < map->height; i++) {
    printf("%s\n", map->map[i]);
  }
}

void init_map(struct Map* map) {
  map->map = malloc(map->height);

  for (int i = 0; i < map->height; i++) {
    char* row = malloc(map->width + 1);  // extra space for null-term char
    memset(row, '.', map->width);
    // adding null-term char at the end so it can be easily printed
    row[map->width] = '\0';
    map->map[i] = row;
  }
}
