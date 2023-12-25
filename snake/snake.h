#ifndef __SNAKE_H
#define __SNAKE_H

typedef struct Snake {
    int** snake;
    int  length;
    int   headX;
    int   headY;
} Snake;

Snake* initSnake(void);
void printSnake(Snake* s);
int updateXdir(int pressed);
int updateYdir(int pressed);
int checkGameOver(Snake* s);
void updateSnakePositions(Snake* s);
void growSnake(Snake* s);
void freeSnake(Snake* s);
#endif