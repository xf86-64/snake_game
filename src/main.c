#include "../include/snake.h"

int main(int argc, char* argv[])
{
    initscr();
  
    DefaultValues dv = {10, 10};
    Node* snake = init_snake(dv);

    getch();
    endwin();
    return 0;
}
