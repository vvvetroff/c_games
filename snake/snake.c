#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include "snake.h"

int main(int argc, char* argv[]){

    /*------------------------------Setup---------------------------*/
    srand(time(NULL));
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

    int dirX, dirY, appleX, appleY, pressed;

    Snake* s = initSnake();

    appleX = rand() % 80;
    appleY = rand() % 25;

    dirX = 1;
    dirY = 0;

    int gameover = 0;
    /*---------------------------The Code---------------------------*/
    while(!gameover){
        pressed = wgetch(win);
        switch(pressed){
            case KEY_UP: 
                dirX = 0;
                dirY = -1;
                break;
            case KEY_DOWN: 
                dirX = 0;
                dirY = 1;
                break;
            case KEY_LEFT:
                dirX = -1;
                dirY = 0;
                break;
            case KEY_RIGHT: 
                dirX = 1;
                dirY = 0;
                break;
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

        erase();

        attron(COLOR_PAIR(2));
        mvaddstr(appleY, appleX, "*");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        printSnake(s);
        attroff(COLOR_PAIR(1));

        refresh();
        usleep(75000);
    }
    freeSnake(s);
    
    endwin();
    return 0;
}