#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
  unsigned int x;
  unsigned int y;
  struct Node *next;
} Node;

typedef struct DefaultValues {
  unsigned int defaultSnakeX;
  unsigned int defaultSnakeY;
  chtype snakeSymbol;
} DefaultValues;
typedef struct Field {
  unsigned int x_max;
  unsigned int y_max;
} Field;

typedef enum { LEFT, RIGHT, UP, DOWN } Directions;

Node *create_node(unsigned int x, unsigned int y);
void insert_at_head(Node **head, Node *node);
void delete_list(Node *head);
void remove_node(Node **head, Node *node_to_remove);

Node *init_snake(DefaultValues _default);
Directions get_direction(Directions *dir, Directions prev_dir);
void move_snake(Directions dir, Node **snake_head);
void display(Node *snake);
bool is_beyond_border(Node *snake_head, Field field);
