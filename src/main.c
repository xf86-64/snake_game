#include "../include/snake.h"

[[maybe_unused]] static Node *snake = NULL;

static void signal_of_immediate_exit(int sig) {
  delete_list(snake);
  endwin();
  exit(1);
}

int main(int argc, char *argv[]) {
  initscr();

  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);

  signal(SIGINT, signal_of_immediate_exit);

  unsigned int x_max, y_max;
  getmaxyx(stdscr, y_max, x_max);
  Field field = {x_max, y_max};

  DefaultValues dv = {10, 10};
  snake = init_snake(dv);
  [[maybe_unused]] Node *tmp_ptr = snake;

  Directions dir = RIGHT;
  Directions prev_dir = dir;

  timeout(100);
  while (dir != -1) {
    clear();
    display(snake);

    prev_dir = get_direction(&dir, prev_dir);
    move_snake(dir, &snake);
    refresh();
  }
  delete_list(snake);

  endwin();
  return 0;
}
