#ifndef __SNAKE_H
#define __SNAKE_H

#include <curses.h> // Bonnie and Clyde

typedef struct Snake {
    int** snake;
    int  length;
    int   headX;
    int   headY;
} Snake;

typedef struct Apple {
    int x;
    int y;
} Apple;

typedef struct AppleList {
    Apple** list;
    int      num;
} AppleList;

void snake(void);

void printLogo(void);
WINDOW* startSnake(void);
Snake* initSnake(void);
AppleList* initApples(int num);
void refreshGame(Snake* s, AppleList* a);
void printSnake(Snake* s);
void printApples(AppleList* a);
int checkGameOver(Snake* s);
void checkIfEaten(Snake* s, AppleList* a);
void updateSnakePositions(Snake* s);
void growSnake(Snake* s);
void freeSnake(Snake* s);
void trashApples(AppleList* a);
#endif
