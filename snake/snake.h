#ifndef __SNAKE_H
#define __SNAKE_H

#include <curses.h>

typedef struct Snake {
    int** snake;
    int  length;
    int   headX;
    int   headY;
} Snake;

void printLogo(void);
WINDOW* startSnake(void);
void snake(void);
Snake* initSnake(void);
void refreshSnake(Snake* s, int aX, int aY);
void printSnake(Snake* s);
int checkGameOver(Snake* s);
void updateSnakePositions(Snake* s);
void growSnake(Snake* s);
void freeSnake(Snake* s);
#endif
