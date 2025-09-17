#include <stdlib.h>
#include <time.h>
#define FRAMES_PER_APPLE 10
#define MAX_FAILS 100

#include "../include/Map.h"

int frames_to_apple = FRAMES_PER_APPLE;

int try_to_place_apple(struct Map *map) {
  srand(time(NULL));

  // selecting row
  int y = rand() % map->height;
  // selecting col
  int x = rand() % map->width;

  // retrun true if successful, otherwise false
  if (map->map[y][x] == '.') {
    map->map[y][x] = '@';
    return 1;
  }
  return 0;
}

void place_apple_where_possible(struct Map *map) {
  for (int y = 0; y < map->height; y++) {
    for (int x = 0; x < map->width; x++) {
      if (map->map[y][x] == '.') {
        map->map[y][x] = '@';
        return;
      }
    }
  }
}

void update_apples(struct Map *map) {
  if (frames_to_apple-- == 0) {
    frames_to_apple = FRAMES_PER_APPLE;

    int fails = 0;
    while (!try_to_place_apple(map)) {
      if (fails++ >= MAX_FAILS) {
        // place it in the first available spot
        place_apple_where_possible(map);
        break;
      }
    }
  }
}