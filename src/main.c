#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/Apple.h"
#include "../include/Map.h"
#include "../include/Snake.h"

#define FRAME_INTERVAL_MS 150000

void print_title(void) {
  start_color();
  init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
  attron(COLOR_PAIR(1));
  attron(A_STANDOUT);
  printw("CSnake\n");
  attroff(A_STANDOUT);
  attroff(COLOR_PAIR(1));
}

int main(int argc, char* argv[]) {
  double loop_interval_s = 1.5;

  int width = 60, height = 20;

  if (argc >= 3) {
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    if (argc > 3) {
      loop_interval_s = atof(argv[3]);
    }
  }

  const double loop_interval_micros = loop_interval_s * 100000;

  // initializing ncurses
  initscr();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  noecho();
  cbreak();

  // Initializing map
  struct Map map = {.width = width, .height = height};
  init_map(&map);

  // Initializing snake
  struct Snake snake;
  init_snake(&snake, &map);

  // Drawing first frame
  put_snake_in_map(&snake);
  print_title();
  print_map(&map);
  printw("Score: %d\n", snake.size);
  refresh();

  // game loop
  while (1) {
    usleep(loop_interval_micros);

    // returns true when you are out of bounds
    if (move_snake(&snake, &map)) {
      endwin();
      printf_map(&map);
      printf("Score: %d\n", snake.size);
      printf("Game over!\n");

      // freeing allocated memory
      free(snake.positions);
      for (int i = 0; i < map.height; i++) free(map.map[i]);
      free(map.map);
      break;
    };

    update_apples(&map);

    clear();
    print_title();
    print_map(&map);
    printw("Score: %d\n", snake.size);
    refresh();
  }
}