#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>
#include "snake.h"

/* TODOs
    - Start screen 
    - Game over screen
    - More apples at one time
    - Snake "enlarging"
    - Snake skins?
    - Speed difficulty, or just difficulty in general
    - Pause menu?

*/


int main(int argc, char* argv[]){

    /*------------------------------Setup---------------------------*/
    srand(time(NULL));
    WINDOW* win = startSnake();

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
        usleep(70000);
    }
    freeSnake(s);
    
    endwin();
    return 0;
}