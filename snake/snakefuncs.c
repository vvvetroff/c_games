#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include "snake.h"

WINDOW* startSnake(void){
    initscr();
    refresh();
    WINDOW* win = newwin(25, 80, 0, 0);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);   
    init_pair(2, COLOR_WHITE, COLOR_YELLOW); 
    assume_default_colors(COLOR_GREEN, COLOR_GREEN); //changes the "default" terminal colors
    wrefresh(win);
    keypad(win, TRUE);
    nodelay(win, TRUE); // makes getch NON-BLOCKING, I HATE YOU STACKOVERFLOW
    curs_set(0);
    return win;
}

Snake* initSnake(void){
    Snake* s    = (Snake*)malloc(sizeof(Snake));
    s->length   = 1;
    s->headX    = 5;
    s->headY    = 13;
    s->snake    = (int**)malloc(sizeof(int*));
    s->snake[0] = (int*)malloc(2*sizeof(int));
    s->snake[0][0] = s->headY;
    s->snake[0][1] = s->headX;
    return s;
}

void printSnake(Snake* s){
    for(int snakePart = 0; snakePart < s->length; snakePart++){
        int partY = s->snake[snakePart][0];
        int partX = s->snake[snakePart][1];
        if(snakePart==0) 
            mvaddstr(partY, partX, "@"); 
        else
            mvaddstr(partY, partX, "o"); 
    }
}

int checkGameOver(Snake* s){
    int result = 0;
    for(int i = 1; i < s->length; i++)
        if(s->headY==s->snake[i][0] && s->headX==s->snake[i][1])
            result = 1;

    if(s->headX < 0)  result = 1;
    if(s->headX > 79) result = 1;
    if(s->headY < 0)  result = 1;
    if(s->headY > 24) result = 1;

    return result;
}

void updateSnakePositions(Snake* s){
    int changeXto = s->headX, changeYto = s->headY;

    for(int snakePart = 0; snakePart < s->length; snakePart++){
        int prevY = s->snake[snakePart][0];
        int prevX = s->snake[snakePart][1]; 
        s->snake[snakePart][0] = changeYto;
        s->snake[snakePart][1] = changeXto;
        changeYto = prevY;
        changeXto = prevX;
    }
}

void growSnake(Snake* s){
    s->length += 1;
    s->snake = (int**)realloc(s->snake, (s->length)*sizeof(int*));
    s->snake[(s->length)-1] = (int*)malloc(2*sizeof(int));
}

void freeSnake(Snake* s){
    for(int snakePart = 0; snakePart < s->length; snakePart++){
        free(s->snake[snakePart]);
    }
    free(s->snake);
    free(s);
}
