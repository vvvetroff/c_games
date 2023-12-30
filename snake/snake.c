#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
*/

int main(int argc, char* argv[]){
    initscr();
    WINDOW* startmenu = newwin(25,80,0,11);
    curs_set(0);
    printLogo();
    mvprintw(12, 20, "by vvvetroff, Github: github.com/vvvetroff");
    mvprintw(14, 25, "Press any key to continue");
    getch();
    snake();
    endwin();
    return 0;
}
