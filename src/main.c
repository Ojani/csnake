#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/Apple.h"
#include "../include/Map.h"
#include "../include/Snake.h"

#define FRAME_INTERVAL_MS 150000

int main() {
  // Initializing map
  struct Map map = {.width = 60, .height = 20};
  init_map(&map);

  // Initializing snake
  struct Snake snake;
  init_snake(&snake, &map);

  // placing snake in map the first time and printing map
  put_snake_in_map(&snake);
  print_map(&map);

  // game loop
  while (1) {
    usleep(FRAME_INTERVAL_MS);

    // returns true when you are out of bounds
    if (move_snake(&snake, &map)) {
      printf("You lost!\n");
      print_map(&map);

      // freeing allocated memory (not working fully)
      free(snake.positions);
      for (int i = 0; i < map.height; i++) free(map.map[i]);
      free(map.map);
      break;
    };

    update_apples(&map);

    print_map(&map);
  }
}