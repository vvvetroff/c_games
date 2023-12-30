#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include "snake.h"

void printLogo(void){
    FILE* file = fopen("logo.txt", "r");
    char str[256];
    while(fgets(str, sizeof(str),file) != NULL)
        printw("%s", str);
    fclose(file);
}

WINDOW* startSnake(void){
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

void snake(void){
    srand(time(NULL));
    WINDOW* win = startSnake();

    int dirX, dirY, appleX, appleY, pressed;

    Snake* s = initSnake();

    appleX = rand() % 80;
    appleY = rand() % 25;

    dirX = 1;
    dirY = 0;

    int gameover = 0;
    while(!gameover){
        pressed = wgetch(win);
        switch(pressed){
            case KEY_UP: 
                dirX = 0;  dirY = -1; break;
            case KEY_DOWN: 
                dirX = 0;  dirY = 1;  break;
            case KEY_LEFT:
                dirX = -1; dirY = 0;  break;
            case KEY_RIGHT: 
                dirX = 1;  dirY = 0;  break;
        }
        s->headX += dirX;
        s->headY += dirY;
        gameover = checkGameOver(s);
        if(s->headX==appleX && s->headY==appleY){
            appleX = rand() % 80;
            appleY = rand() % 25;
            growSnake(s);
        }
        updateSnakePositions(s);
        refreshSnake(s, appleX, appleY);
        usleep(70000);
    }
    freeSnake(s);
    nodelay(win, FALSE);
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

void refreshSnake(Snake* s, int aX, int aY){
    erase();
    attron(COLOR_PAIR(2));
    mvaddstr(aY, aX, "*");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(1));
    printSnake(s);
    attroff(COLOR_PAIR(1));
    refresh();
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
