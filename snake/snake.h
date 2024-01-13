#ifndef __SNAKE_H
#define __SNAKE_H

#include <curses.h> // Bonnie and Clyde

typedef struct Coords {
    int x;
    int y;
} Coords;

typedef struct AppleList {
    Coords** list;
    int      num;
} AppleList;

typedef struct Snake {
    Coords** snake;
    int     length;
    int      headX;
    int      headY;
} Snake;

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
