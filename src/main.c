#include "../include/snake.h"

extern int atoi(const char *str);

Node *snake = NULL;
Node *food = NULL;

static void signal_of_immediate_exit(int sig) {
  delete_list(snake);
  endwin();
  exit(1);
} // signal handler function

int main(int argc, char *argv[]) {

  int capacity_of_list_food = 10;
  short int index = 1;
  const char *arg = argv[index];
  if (arg != NULL) {
    int current_arg_num = atoi(arg);
    if (current_arg_num > 3)
      capacity_of_list_food = current_arg_num;
  }
  srand(time(0));
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  keypad(stdscr, true);
  nodelay(stdscr, true);
  signal(SIGINT, signal_of_immediate_exit); // handle ctrl+c signal

  unsigned int x_max, y_max;
  getmaxyx(stdscr, y_max, x_max);
  Field field = {x_max, y_max};

  DefaultValues dv = {10, 10};
  snake = init_snake(dv);
  food = fill_food_list(capacity_of_list_food, field);
  Directions dir = RIGHT; // default direction
  Directions prev_dir = dir;

  timeout(100);
  bool is_delete_tail = false;
  bool collision_with_body = false;
  while (dir != -1 && !is_beyond_border(snake, field) && food != NULL &&
         !collision_with_body) {
    clear();
    display(snake, ACS_BLOCK);

    generate_food(food, '(');
    prev_dir = get_direction(&dir, prev_dir);

    collision_with_body = move_snake(dir, &snake, &is_delete_tail);

    is_delete_tail = detect_eaten_food(&food, snake);
    refresh();
  }
  // win situation processing
  if (food == NULL && dir != -1 && is_beyond_border(snake, field)) {
    delete_list(snake);
    endwin();
  }
  delete_list(snake);
  delete_list(food);
  endwin();
  return 0;
}
