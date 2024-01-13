#ifndef __SNAKE_H
#define __SNAKE_H

#include <curses.h> // Bonnie and Clyde

typedef struct Coords {
    int x;
    int y;
} Coords;

typedef struct Apples {
    Coords** list;
    int      num;
} Apples;

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
Apples* initApples(int num);
void refreshGame(Snake* s, Apples* a);
void printSnake(Snake* s);
void printApples(Apples* a);
int checkGameOver(Snake* s);
void checkIfEaten(Snake* s, Apples* a);
void moveSnake(Snake* s);
void growSnake(Snake* s);
void freeSnake(Snake* s);
void trashApples(Apples* a);
#endif
