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
    snake();
    endwin();
    return 0;
}
