#include <bits/types/struct_timeval.h>
#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
  unsigned int x;
  unsigned int y;
  struct Node *next;
} Node;

typedef struct DefaultValues {
  unsigned int defaultSnakeX;
  unsigned int defaultSnakeY;
  chtype snakeSymbol;
  chtype foodSymbol;
} DefaultValues;

typedef struct Field {
  unsigned int x_max;
  unsigned int y_max;
} Field;

typedef enum { LEFT, RIGHT, UP, DOWN } Directions;

void delete_list(Node *head);
Node *init_snake(DefaultValues _default);

Directions get_direction(Directions *dir, Directions prev_dir);
bool move_snake(Directions dir, Node **snake_head, bool *is_delete_tail);
void display(Node *snake, const chtype symbol);
bool is_beyond_border(Node *snake_head, Field field);
Node *fill_food_list(unsigned int foodCount, Field field);
void generate_food(Node *food_list, const chtype symbol);
bool detect_eaten_food(Node **food_list, Node *snake_head);
