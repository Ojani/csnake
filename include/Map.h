#ifndef MAP_H
#define MAP_H

struct Map {
  int width;
  int height;
  char** map;
};

void print_map(struct Map* map);

void init_map(struct Map* map);

#endif  // MAP_H