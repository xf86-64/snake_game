#include "../include/snake.h"
#include <stdlib.h>

Node* create_node(unsigned int x, unsigned int y)
{
    Node* node = malloc(sizeof(Node));
    node->x = x;
    node->y = y;
    node->next = NULL;
    return node;
}
void insert_at_head(Node** head, Node* node)
{
    node->next = *head;
    *head = node;
}
void remove_node(Node** head, Node* node_to_remove)
{
    if(*head == node_to_remove)
    {
        *head = node_to_remove->next;
        free(head);
        return;
    }
    Node* ptr = *head;

    while(ptr && ptr->next != node_to_remove)
    {
        ptr = ptr->next;
    }
    if(ptr == NULL) return;
    ptr->next = node_to_remove->next;
    free(node_to_remove);
}
void delete_list(Node* head)
{
    Node* ptr = head;
    while(ptr)
    {
        Node* next = ptr->next;
        free(head);
        ptr = next;
    }
}
Node* init_snake(DefaultValues _default)
{
    Node* snake_head = create_node(_default.defaultSnakeX, _default.defaultSnakeY); 
    Node* snake_body = create_node(_default.defaultSnakeX+1, _default.defaultSnakeY);
    insert_at_head(&snake_body, snake_head);
    snake_body = snake_head;
    Node* ptr = snake_body;
    while(ptr)
    {
        mvaddch(ptr->y, ptr->x, ACS_BLOCK);
        ptr = ptr->next;
    }
    refresh();
    return snake_body;
}
