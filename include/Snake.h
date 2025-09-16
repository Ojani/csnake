#ifndef SNAKE_H
#define SNAKE_H

#include "../include/Map.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Snake {
  enum Direction direction;  // direction we are travelling
  char** positions;  // contains pointer to a cell, the head is at index 0
  int size;
  int x;
  int y;
};

void init_snake(struct Snake* snake, struct Map* map);

void put_snake_in_map(struct Snake* snake);

int move_snake(struct Snake* snake, struct Map* map);

#endif  // SNAKE_H