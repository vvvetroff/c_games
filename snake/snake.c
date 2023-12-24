#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <term.h>

void printSnake(int** snake, int snakeLength){
    for(int snakePart = 0; snakePart < snakeLength; snakePart++){
        int partY = snake[snakePart][0];
        int partX = snake[snakePart][1];
        if(snakePart==0) 
            mvaddstr(partY, partX, "@"); 
        else
            mvaddstr(partY, partX, "o"); 
    }
}

int checkGameOver(int** snake, int snakeLength, int headX, int headY){
    int result = 0;
    for(int i = 1; i < snakeLength; i++)
        if(headY==snake[i][0] && headX==snake[i][1])
            result = 1;

    if(headX < 0)  result = 1;
    if(headX > 79) result = 1;
    if(headY < 0)  result = 1;
    if(headY > 24) result = 1;

    return result;
}

void updateSnakePositions(int** snake, int curX, int curY, int snakeLength){
    int changeXto = curX, changeYto = curY;

    for(int snakePart = 0; snakePart < snakeLength; snakePart++){
        int prevY = snake[snakePart][0];
        int prevX = snake[snakePart][1]; 
        snake[snakePart][0] = changeYto;
        snake[snakePart][1] = changeXto;
        changeYto = prevY;
        changeXto = prevX;
    }
}

void freeSnake(int** snake, int snakeLength){
    for(int snakePart = 0; snakePart < snakeLength; snakePart++){
        free(snake[snakePart]);
    }
    free(snake);
}

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

    int sX, sY, dirX, dirY, appleX, appleY, sLength = 1, pressed;

    int** snake = (int**)malloc(sLength*sizeof(int*));
    snake[0] = (int*)malloc(2*sizeof(int));

    sY = 13;
    sX = 5;
    appleX = rand() % 80;
    appleY = rand() % 25;

    snake[0][0] = sY;
    snake[0][1] = sX;

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

        sX += dirX;
        sY += dirY;

        gameover = checkGameOver(snake, sLength, sX, sY);

        if(sX==appleX && sY==appleY){
            appleX = rand() % 80;
            appleY = rand() % 25;

            sLength += 1;
            snake = (int**)realloc(snake, sLength*sizeof(int*));
            snake[sLength-1] = (int*)malloc(2*sizeof(int));
        }

        updateSnakePositions(snake, sX, sY, sLength);

        erase();

        attron(COLOR_PAIR(2));
        mvaddstr(appleY, appleX, "*");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        printSnake(snake, sLength);
        attroff(COLOR_PAIR(1));

        refresh();
        usleep(75000);
    }
    freeSnake(snake, sLength);
    
    endwin();
    return 0;
}