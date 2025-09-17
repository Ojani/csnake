#include "../include/Snake.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_snake(struct Snake* snake, struct Map* map) {
  snake->direction = LEFT;
  snake->x = map->width - 1;
  snake->y = 0;
  // allocating space for the pointers
  snake->positions = malloc(map->width * map->height * sizeof(char*));
  // placing snake in the top right
  snake->positions[0] = &map->map[snake->y][snake->x];
  snake->size = 1;
}

void put_snake_in_map(struct Snake* snake) {
  for (int i = 0; i < snake->size; i++) {
    *snake->positions[i] = '#';
  }
}

void eat_apple(struct Snake* snake, struct Map* map, char* prev_tail) {
  if (++snake->size == (map->width * map->height)) {
    // WON THE GAME
  }

  // making tail point to the same memory location as the previous tail
  snake->positions[snake->size - 1] = prev_tail;
}

int move_snake(struct Snake* snake, struct Map* map) {
  // checking user input to see if we need to change direction
  int last_usr_input = getch();

  if (last_usr_input != ERR) {
    // converting lowercase to uppsercase
    if (last_usr_input >= 'a' && last_usr_input <= 'z') last_usr_input -= 32;

    switch (last_usr_input) {
      case ('W'):
      case (KEY_UP):
        if (snake->direction != DOWN) snake->direction = UP;
        break;
      case ('A'):
      case (KEY_LEFT):
        if (snake->direction != RIGHT) snake->direction = LEFT;
        break;
      case ('S'):
      case (KEY_DOWN):
        if (snake->direction != UP) snake->direction = DOWN;
        break;
      case ('D'):
      case (KEY_RIGHT):
        if (snake->direction != LEFT) snake->direction = RIGHT;
        break;
    }
  }

  // preserving previous tail position
  char* prev_tail = snake->positions[snake->size - 1];

  short out_of_bounds = 0;

  switch (snake->direction) {
    case UP:
      if (snake->y == 0) {
        out_of_bounds = 1;
      } else {
        snake->y--;
      }
      break;
    case DOWN:
      if (snake->y == map->height - 1) {
        out_of_bounds = 1;
      } else {
        snake->y++;
      }
      break;
    case LEFT:
      if (snake->x == 0) {
        out_of_bounds = 1;
      } else {
        snake->x--;
      }
      break;
    case RIGHT:
      if (snake->x == map->width - 1) {
        out_of_bounds = 1;
      } else {
        snake->x++;
      }
      break;
  }

  if (out_of_bounds) {
    return 1;
  }

  // rotating memory locations to "move" the body towards the head
  for (int i = snake->size - 1; i > 0; i--) {
    snake->positions[i] = snake->positions[i - 1];
  }

  // changing head ptr to the char ptr in the corrext x and y pos
  snake->positions[0] = &map->map[snake->y][snake->x];

  // checking for apple
  if (*snake->positions[0] == '@') {
    eat_apple(snake, map, prev_tail);
  } else {
    // resetting char at tail to the background
    *prev_tail = '.';
  }

  // head hit body
  if (*snake->positions[0] == '#') {
    return 1;
  }

  // changing character at head
  *snake->positions[0] = '#';

  return 0;
}