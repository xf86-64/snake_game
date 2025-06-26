#include <ncurses.h>


typedef struct Node
{
    unsigned int x;
    unsigned int y;
    struct Node* next;
} Node;

typedef struct DefaultValues
{
    unsigned int defaultSnakeX;
    unsigned int defaultSnakeY;
} DefaultValues;

Node* create_node(unsigned int x, unsigned int y);
void insert_at_head(Node** head, Node* node);
void delete_list(Node* head);
void remove_node(Node** head, Node* node_to_remove);

Node* init_snake(DefaultValues _default);
