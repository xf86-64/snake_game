#include "../include/snake.h"

static Node *create_node(unsigned int x, unsigned int y) {
  Node *node = malloc(sizeof(Node));
  node->x = x;
  node->y = y;
  node->next = NULL;
  return node;
}
static inline void insert_at_head(Node **head, Node *node) {
  node->next = *head;
  *head = node;
}

void delete_list(Node *head) {
  Node *ptr = head;
  while (ptr) {
    Node *next = ptr->next;
    free(ptr);
    ptr = next;
  }
}
static void remove_node(Node **head, Node *node_to_remove) {
  if (*head == node_to_remove) {
    *head = node_to_remove->next;
    free(head);
    return;
  }
  Node *ptr = *head;

  while (ptr && ptr->next != node_to_remove) {
    ptr = ptr->next;
  }
  if (ptr == NULL)
    return;
  ptr->next = node_to_remove->next;
  free(node_to_remove);
}

Node *init_snake(DefaultValues _default) {
  Node *snake_head =
      create_node(_default.defaultSnakeX, _default.defaultSnakeY);
  Node *snake_body =
      create_node(_default.defaultSnakeX + 1, _default.defaultSnakeY);

  insert_at_head(&snake_body, snake_head);
  snake_body = snake_head;
  Node *ptr = snake_body;
  while (ptr) {
    mvaddch(ptr->y, ptr->x, ACS_BLOCK);
    ptr = ptr->next;
  }
  refresh();
  return snake_head;
}
Directions get_direction(Directions *dir, Directions prev_dir) {
  int ch = getch();
  switch (ch) {
  case KEY_LEFT:
  case 'a':
    if (prev_dir != RIGHT)
      *dir = LEFT;
    break;

  case KEY_RIGHT:
  case 'd':
    if (prev_dir != LEFT)
      *dir = RIGHT;
    break;

  case KEY_UP:
  case 'w':
    if (prev_dir != DOWN)
      *dir = UP;
    break;

  case KEY_DOWN:
  case 's':
    if (prev_dir != UP)
      *dir = DOWN;
    break;
  case 'q':
    *dir = -1;
    break;
  }
  return *dir;
}
static unsigned int getSize(Node *snake) {
  Node *ptr = snake;
  unsigned int count = 0;
  while (ptr) {
    count++;
    ptr = ptr->next;
  }
  return count;
}
bool move_snake(Directions dir, Node **snake_head,
                bool *restrict is_delete_tail) {
  int opX = 0, opY = 0;
  switch (dir) {
  case LEFT:
    opX = -1;
    break;
  case RIGHT:
    opX = 1;
    break;
  case UP:
    opY = -1;
    break;
  case DOWN:
    opY = 1;
    break;
  }
  int size = getSize(*snake_head);
  unsigned int newHeadX = (*snake_head)->x + (opX),
               newHeadY = (*snake_head)->y + (opY);
  Node *new_head = create_node(newHeadX, newHeadY);
  insert_at_head(snake_head, new_head);
  if (!(*is_delete_tail)) {
    Node *ptr = new_head;
    while (ptr->next->next) {
      ptr = ptr->next;
    }

    Node *ptr2 = new_head->next;
    if (size > 2) {
      while (ptr2) {
        if (ptr2->x == new_head->x && ptr2->y == new_head->y)
          return true;
        ptr2 = ptr2->next;
      }
    }
    remove_node(&new_head, ptr->next);
  } else
    *is_delete_tail = false;

  return false;
}

void display(Node *snake, const chtype symbol) {
  Node *ptr = snake;
  while (snake) {
    mvaddch(snake->y, snake->x, symbol);
    snake = snake->next;
  }
  snake = ptr;
}

inline bool is_beyond_border(Node *snake_head, Field field) {
  return (snake_head->x < 0 || snake_head->y <= 0 ||
          snake_head->x > field.x_max || snake_head->y >= field.y_max);
}

Node *fill_food_list(unsigned int foodCount, Field field, Node *snake) {

  Node *ptr_snake = snake;
  unsigned int min_coord_x = 1;
  unsigned int max_coord_x = field.x_max;

  unsigned int min_coord_y = 1;
  unsigned int max_coord_y = field.y_max;

  unsigned int expressionX = max_coord_x - min_coord_x + 1;
  unsigned int expressionY = max_coord_y - min_coord_y + 1;

  Node *head = create_node(rand() % expressionX, rand() % expressionY);
  for (unsigned int i = 0; i < foodCount - 1; i++) {

    Node *generated = create_node(rand() % expressionX, rand() % expressionY);
    Node *ptr = generated;
    while (ptr) {
      if (ptr->x == ptr_snake->x && ptr->y == ptr_snake->y) {
        i--;
        break;
      }
      ptr = ptr->next;
    }
    insert_at_head(&head, generated);
  }
  return head;
}
inline void generate_food(Node *food_list, const chtype symbol) {
  mvaddch(food_list->y, food_list->x, symbol);
}
static void remove_from_food_list(Node **food_list) {
  Node *next = (*food_list)->next;
  free(*food_list);
  *food_list = next;
}
bool detect_eaten_food(Node **food_list, Node *snake_head) {
  if ((*food_list)->x == snake_head->x && (*food_list)->y == snake_head->y) {
    mvaddch((*food_list)->y, (*food_list)->x, ' ');
    remove_from_food_list(food_list);

    return true;
  }
  return false;
}
