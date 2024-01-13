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
    Snake* s = initSnake();
    AppleList* a = initApples(8);

    int dirX = 1;
    int dirY = 0;

    int gameover = 0;
    while(!gameover){
        int pressed = wgetch(win);
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
        checkIfEaten(s, a);
        updateSnakePositions(s);
        refreshGame(s, a);
        usleep(70000);
    }
    freeSnake(s);
    trashApples(a);
    erase();
    nodelay(win, FALSE);
    use_default_colors();
    endwin();
}

Snake* initSnake(void){
    Snake* s    = (Snake*)malloc(sizeof(Snake));
    s->length   = 1;
    s->headX    = 5;
    s->headY    = 13;
    s->snake    = (Coords**)malloc(sizeof(Coords*));
    s->snake[0] = (Coords*)malloc(sizeof(Coords));
    s->snake[0]->x = 5;
    s->snake[0]->y = 13;
    return s;
}

AppleList* initApples(int num){
    AppleList* apples = (AppleList*)malloc(sizeof(AppleList));
    apples->num = num;
    apples->list = (Coords**)malloc(sizeof(Coords*) * num);
    for(int i = 0; i < num; i++){
        apples->list[i] = (Coords*)malloc(sizeof(Coords));
        apples->list[i]->x = rand() % 80;
        apples->list[i]->y = rand() % 25;
    }
    return apples;
}

void refreshGame(Snake* s, AppleList* a){
    erase();

    printApples(a);
    printSnake(s);
    
    refresh();
}

void printSnake(Snake* s){
    attron(COLOR_PAIR(1));
    for(int snakePart = 0; snakePart < s->length; snakePart++){
        int partY = s->snake[snakePart]->y;
        int partX = s->snake[snakePart]->x;
        if(snakePart==0) 
            mvaddstr(partY, partX, "@"); 
        else
            mvaddstr(partY, partX, "o"); 
    }
    attroff(COLOR_PAIR(1));
}

void printApples(AppleList* a){
    attron(COLOR_PAIR(2));
    for(int apple = 0; apple < a->num; apple++){
        Coords* curCoord = a->list[apple];
        mvaddstr(curCoord->y, curCoord->x, "*"); 
    }
    attroff(COLOR_PAIR(2));
}

int checkGameOver(Snake* s){
    int result = 0;
    for(int i = 1; i < s->length; i++)
        if(s->headY==s->snake[i]->y && s->headX==s->snake[i]->x)
            result = 1;

    if(s->headX < 0)  result = 1;
    if(s->headX > 79) result = 1;
    if(s->headY < 0)  result = 1;
    if(s->headY > 24) result = 1;

    return result;
}

void checkIfEaten(Snake* s, AppleList* a){
    for(int apple = 0; apple < a->num; apple++){
        Coords* curCoords = a->list[apple];
        if(s->headX == curCoords->x && s->headY == curCoords->y){
            curCoords->x = rand() % 80;
            curCoords->y = rand() % 25;
            growSnake(s);
        }
    }
}

void updateSnakePositions(Snake* s){
    int changeXto = s->headX, changeYto = s->headY;

    for(int snakePart = 0; snakePart < s->length; snakePart++){
        int prevY = s->snake[snakePart]->y;
        int prevX = s->snake[snakePart]->x; 
        s->snake[snakePart]->y = changeYto;
        s->snake[snakePart]->x = changeXto;
        changeYto = prevY;
        changeXto = prevX;
    }
}

void growSnake(Snake* s){
    s->length += 1;
    s->snake = (Coords**)realloc(s->snake, (s->length)*sizeof(Coords*));
    s->snake[(s->length)-1] = (Coords*)malloc(sizeof(Coords));
}

void freeSnake(Snake* s){
    for(int snakePart = 0; snakePart < s->length; snakePart++){
        free(s->snake[snakePart]);
    }
    free(s->snake);
    free(s);
}

void trashApples(AppleList* a){
    for(int apple = 0; apple < a->num; apple++){
        free(a->list[apple]);
    }
    free(a->list);
    free(a);
}
