#define _CRT_SECURE_NO_WARNINGS
#include"stdio.h"
#include "conio2.h"
#include <malloc.h>
#include "gameFunc.h"


/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */



int main() {
    gameFunc object;
    
    if (object.boardSize + object.startX > 119 || object.startY + object.boardSize > 29) {
        gotoxy(object.legendX, 1);
        cputs("The board doesn't fit into screen. Please choose smaller board size\n");
    }

    
    object.runGame();

    return 0;
}
