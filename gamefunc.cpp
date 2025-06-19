#define _CRT_SECURE_NO_WARNINGS
#include "gameFunc.h"

void gameFunc::createState() {
    state = (int**)malloc(boardSize * sizeof(int*));
    for (int i = 0; i < boardSize; i++)
        state[i] = (int*)malloc(boardSize * sizeof(int));

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            state[i][j] = 0;
        }
    }
}
// create 2d dynamic array and set all values to 0

void gameFunc::createChecked() {
    checked = (int**)malloc(boardSize * sizeof(int*));
    for (int i = 0; i < boardSize; i++)
        checked[i] = (int*)malloc(boardSize * sizeof(int));

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            checked[i][j] = 0;
        }
    }
}
// create 2d dynamic array and set all values to 0

void gameFunc::drawLegend() {

    gotoxy(legendX, 1);                                                     
    cputs("Jan Pastucha, 193662");
    gotoxy(legendX, 2);
    cputs("q       = exit");
    gotoxy(legendX, 3);
    cputs("arrows  = moving");
    gotoxy(legendX, 4);
    cputs("space   = cancel current action");
    gotoxy(legendX, 5);
    cputs("enter   = confirm choice and end players turn");
    gotoxy(legendX, 7);
    cputs("i       = put a stone");
    gotoxy(legendX, 8);
    cputs("n       = start a new game");
    gotoxy(legendX, 9);
    cputs("s       = save the game state");
    gotoxy(legendX, 10);
    cputs("l       = load the game state");
    sprintf(score, "White score: %f", whiteScore);
    gotoxy(legendX, 15);
    cputs(score);
    sprintf(score, "Black score: %f", blackScore);
    gotoxy(legendX, 16);
    cputs(score);
}
// draw legend

void gameFunc::drawBoard() {
    int x = 1, y = 1;
    for (x; x < boardSize + 1; x++) {
        gotoxy(startX + x, startY);                                 // upper border               
        cputs("#");                                                 // draw a #
        gotoxy(startX + x, startY + boardSize + 1);                 // bottom border
        cputs("#");                                                 // draw a #
    }
    for (y; y < boardSize + 3; y++) {
        gotoxy(startX, y);                                          // left border                            
        cputs("#");                                                 // draw a #
        gotoxy(startX + boardSize + 1, y);                          // right border
        cputs("#");                                                 // draw a #
    }

}
// draw board with borders

void gameFunc::swapTurn() {
    if (previousTurn == 1) {                // check if previous turn was white
        currentTurn = 0;                    // set current turn to black
        previousTurn = currentTurn;         // set previous turn variable to black
    }
    else if (previousTurn == 0) {           // check if previous turn was black
        currentTurn = 1;                    // set current turn to white
        previousTurn = currentTurn;         // set previous turn variable to white
    }
}
// swap turn 

int gameFunc::turn() {
    if (previousTurn == 1) {                // check if previous turn was white        
        currentTurn = 0;                    // set current turn to black
    }
    else if (previousTurn == 0) {           // check if previous turn was black   
        currentTurn = 1;                    // set current turn to white
    }
    return currentTurn;                     // return whose turn is right now
}
// check whose turn is right now
// turn 0 - black
// turn 1 - white

void gameFunc::resetGame() {
    int x = startX + 1;                                 // set x to starting cursor position
    int y = startY + 1;                                 // set y to starting cursor position
    whiteScore = 0;                                     // reset white score
    blackScore = 0;                                     // reset black score
    whitePrisoners = 0;                                 // reset number of white prisoners
    blackPrisoners = 0;                                 // reset number of black prisoners
    blackTerritory = 0;                                 // reset black territory count
    whiteTerritory = 0;                                 // reset white territory count
    put = false;                                        // set that the stone wasnt put yet
    approved = true;                                    // set that you can put a stone
    gamestarted = false;                                // set that game didnt started yet and you can introduce a handicap
    gotoxy(x, y);                                       // move to starting position
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            state[i][j] = 0;                            // clear the board
        }
    }
    if (previousTurn == 0) {                            // check if previous turn was black
        currentTurn = 0;                                // sets turn to black
    }
}
// restart game to initial state

void gameFunc::resetChecked() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            checked[i][j] = 0;                          // sets all points on board to be non checked
        }
    }
}
// reset checked array

void gameFunc::drawGameState() {
    int x = startX + 1;                                     // x position where board starts
    int y = startY + 1;                                     // y position where board starts
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            gotoxy(x + i, y + j);                           // move around the board
            if (state[i][j] == 1) {                         // check if value of current position is black
                cputs("B");                                 // print b to board
            }
            else if (state[i][j] == 2) {                    // check if value of current position is white
                cputs("W");                                 // print w to board
            }
        }
    }
}
// draw where stones are placed and which color

bool gameFunc::clearSpot(int x, int y) {
    return state[x][y] == 0;
}
// checks if spot on which player is trying to put a stone is already taken

bool gameFunc::hasLiberty(int x, int y) {
    bool found = false;
    if (x != 0) {                                                   // checks if point isnt placed next to left border
        if (state[x - 1][y] == 0) found = true;                     // checks if point has empty spot on left
    }
    if (x != boardSize - 1) {                                       // checks if point isnt placed next to right border
        if (state[x + 1][y] == 0) found = true;                     // checks if point has empty spot on right
    }
    if (y != 0) {                                                   // checks if point isnt placed next to top border
        if (state[x][y - 1] == 0) found = true;                     // checks if point has empty spot on top
    }
    if (y != boardSize - 1) {                                       // checks if point isnt placed next to bottom border
        if (state[x][y + 1] == 0) found = true;                     // checks if point has empty spot on bottom
    }
    return found;                                                   // return if any empty spot was found
}
// checks if spot on which player is trying to put a stone has at least one liberty

int gameFunc::sameColor() {
    if (turn() == 0) {
        return 1;
    }
    else {
        return 2;
    }
}

int gameFunc::oppositeColor() {
    if (turn() == 0) {
        return 2;
    }
    else {
        return 1;
    }
}

bool gameFunc::canEasyCapture(int x, int y) {                                          // check if its blacks turn
    if (x == 0) {                                           // check if stone is next to left border
        if (y == 0) {                                       // check if stone is next to top border
            if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x + 1][y + 1] == sameColor()) return true;   
            if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y + 1] == sameColor()) return true;
            return false;
        } else if (y == boardSize - 1) {                    // check if stone is next to bottom border
            if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x + 1][y - 1] == sameColor()) return true;
            if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y - 1] == sameColor()) return true;
            return false;
        }
        if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x + 1][y + 1] == sameColor()) return true;
        if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x + 1][y - 1] == sameColor()) return true;
    }
    if (x == 1 && state[x - 1][y] == oppositeColor() && state[x - 1][y + 1] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
    if (y == 0 && x > 1 && x < boardSize - 2) {
        if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y + 1] == sameColor()) return true;
        if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y + 1] == sameColor()) return true;
    }
    if (y == 1 && x > 1 && x < boardSize - 2 && state[x][y - 1] == oppositeColor() && state[x + 1][y - 1] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
    if (x == boardSize - 1) {
        if (y == 0) {
            if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
            if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
            return false;
        }
        else if (y == boardSize - 1) {
            if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
            if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
            return false;
        }
        if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x - 1][y + 1] == sameColor()) return true;
        if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
    }
    if (x == boardSize - 2 && state[x + 1][y] == oppositeColor() && state[x + 1][y + 1] == sameColor() && state[x + 1][y - 1] == sameColor()) return true;
    if (y == boardSize - 1 && x > 1 && x < boardSize - 2) {
        if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y - 1] == sameColor()) return true;
        if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y - 1] == sameColor()) return true;
    }
    if (y == boardSize - 2 && x > 1 && x < boardSize - 2 && state[x][y + 1] == oppositeColor() && state[x + 1][y + 1] == sameColor() && state[x - 1][y + 1] == sameColor()) return true;
    if (x != 0 && x != 1 && y != 0 && y != 1 && x != boardSize - 1 && x != boardSize - 2 && y != boardSize - 1 && y != boardSize - 2) {
        if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == 1 && state[x - 1][y - 1] == sameColor() && state[x - 1][y + 1] == sameColor()) return true;
        if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == 1 && state[x + 1][y - 1] == sameColor() && state[x + 1][y + 1] == sameColor()) return true;
        if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == 1 && state[x - 1][y - 1] == sameColor() && state[x + 1][y - 1] == sameColor()) return true;
        if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == 1 && state[x - 1][y + 1] == sameColor() && state[x + 1][y + 1] == sameColor()) return true;
    }
    return false;                                           // if any of those options didnt return true then you cant capture
}
// checks if stone can easy capture other stone

bool gameFunc::blockRepeatKo() {
    if (doneko == true) {                   // check if ko was done
        return true;
    }
    else {
        return false;
    }
}
// blocks placement of stone that returns game to previous state

void gameFunc::captureBasic(int x, int y) {
    if (canEasyCapture(x, y)) {
        if (x == 0) {
            if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x + 1][y + 1] == sameColor()) {
                state[x][y + 1] = 0;
                blackPrisoners++;
            }
            if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x + 1][y - 1] == sameColor()) {
                state[x][y - 1] = 0;
                blackPrisoners++;
            }
        }
        else if (x == 1 && state[x - 1][y] == oppositeColor() && state[x - 1][y + 1] == sameColor() && state[x - 1][y - 1] == sameColor()) {
            state[x - 1][y] = 0;
            blackPrisoners++;
        }
        else if (y == 0) {
            if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y + 1] == sameColor()) {
                state[x + 1][y] = 0;
                blackPrisoners++;
            }
            if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y + 1] == sameColor()) {
                state[x - 1][y] = 0;
                blackPrisoners++;
            }
        }
        else if (y == 1 && state[x][y - 1] == oppositeColor() && state[x + 1][y - 1] == sameColor() && state[x - 1][y - 1] == sameColor()) {
            state[x][y - 1] = 0;
            blackPrisoners++;
        }
        else if (x == boardSize - 1) {
            if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x - 1][y + 1] == sameColor()) {
                state[x][y + 1] = 0;
                blackPrisoners++;
            }
            if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x - 1][y - 1] == sameColor()) {
                state[x][y - 1] = 0;
                blackPrisoners++;
            }
        }
        else if (x == boardSize - 2 && state[x + 1][y] == oppositeColor() && state[x + 1][y + 1] == sameColor() && state[x + 1][y - 1] == sameColor()) {
            state[x + 1][y] = 0;
            blackPrisoners++;
        }
        else if (y == boardSize - 1) {
            if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y - 1] == sameColor()) {
                state[x + 1][y] = 0;
                blackPrisoners++;
            }
            if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y - 1] == sameColor()) {
                state[x - 1][y] = 0;
                blackPrisoners++;
            }
        }
        else if (y == boardSize - 2 && state[x][y + 1] == oppositeColor() && state[x + 1][y + 1] == sameColor() && state[x - 1][y + 1] == sameColor()) {
            state[x][y + 1] = 0;
            blackPrisoners++;
        }
        if (x != 0 && x != 1 && y != 0 && y != 1 && x != boardSize - 1 && x != boardSize - 2 && y != boardSize - 1 && y != boardSize - 2) {
            if (state[x - 1][y] == oppositeColor() && state[x - 2][y] == sameColor() && state[x - 1][y - 1] == sameColor() && state[x - 1][y + 1] == sameColor()) {
                state[x - 1][y] = 0;
                blackPrisoners++;
            }
            else if (state[x + 1][y] == oppositeColor() && state[x + 2][y] == sameColor() && state[x + 1][y - 1] == sameColor() && state[x + 1][y + 1] == sameColor()) {
                state[x + 1][y] = 0;
                blackPrisoners++;
            }
            else if (state[x][y - 1] == oppositeColor() && state[x][y - 2] == sameColor() && state[x - 1][y - 1] == sameColor() && state[x + 1][y - 1] == sameColor()) {
                state[x][y - 1] = 0;
                blackPrisoners++;
            }
            else if (state[x][y + 1] == oppositeColor() && state[x][y + 2] == sameColor() && state[x - 1][y + 1] == sameColor() && state[x + 1][y + 1] == sameColor()) {
                state[x][y + 1] = 0;
                blackPrisoners++;
            }
        }
    }
}
// basic capture as black

void gameFunc::place(int x, int y, int z) {
    resetChecked();
    state[x][y] = z;                                            // add number to state array at position of cursor
}
// 1 - black
// 2 - white

bool gameFunc::alreadyChecked(int x, int y) {
    if (checked[x][y] == 1) return true;                                                // checks if current stone was already checked
    return false;
}
// checks if that place on board was already checked

int gameFunc::sameNotCheckedCount(int x, int y) {
    int same = 0;
    if (x != 0 && state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0) same++;                 // check if stone on left is same as current and wasnt checked
    if (x != boardSize - 1 && state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0) same++;     // check if stone on right is same as current and wasnt checked
    if (y != 0 && state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0) same++;                 // check if stone on up is same as current and wasnt checked
    if (y != boardSize - 1 && state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0) same++;     // check if stone on bottom is same as current and wasnt checked
    return same;
}
// returns value of adjacent stones that were checked and have same color as current stone

bool gameFunc::canComplex(int x, int y) {
    checked[x][y] = 1;
    if (hasLiberty(x, y)) {                                                                  // checks if there are any empty places around stone
        return false;                                                                   // if yes then there is no way of capturing
    }
    else {                                                                                    // if there are no empty spaces there is possibility of capturing    
        if (sameNotCheckedCount(x, y) == 1) {
            if (x != 0) {                                               // checks if there is only 1 stone adjacent of same color that wasnt captured
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0) {                 // checks if color of the left stone is same as currents and if it wasnt already checked
                    if (hasLiberty(x - 1, y)) {                                     // checks if there are no blank spaces around stone on the left
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x - 1][y] = 1;
                        canComplex(x - 1, y);                                                   // call function on left stone
                        return true;                                                            // if function doesnt return false during recursive calling it means you can capture
                    }
                }
            }
            if (x != boardSize - 1) {
                if (state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0) {                 // checks if color of the right stone is same as currents and if it wasnt already checked
                    if (hasLiberty(x + 1, y)) {
                        resetChecked();
                        return false;
                    }
                    else {                                                      // marks spot as already checked
                        checked[x + 1][y] = 1;
                        canComplex(x + 1, y);
                        return true;
                    }
                }
            }
            if (y != boardSize - 1) {
                if (state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0) {                // checks if color of the bottom stone is same as currents and if it wasnt already checked
                    if (hasLiberty(x, y + 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x][y + 1] = 1;
                        canComplex(x, y + 1);
                        return true;
                    }                                               // call again function to check the uppper stone
                }
            }
            if (y != 0) {
                if (state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0) {                 // checks if color of the upper stone is same as currents and if it wasnt already checked
                    if (hasLiberty(x, y - 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x][y - 1] = 1;
                        canComplex(x, y - 1);
                        return true;
                    }                                                      // call again function to check the bottom stone
                }
            }
        }
        else if (sameNotCheckedCount(x, y) == 2) {
            if (x != 0 && x != boardSize - 1) {
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0 && state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0) {         // left-right              
                    if (hasLiberty(x - 1, y) || hasLiberty(x + 1, y)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x - 1][y] = 1;
                        checked[x + 1][y] = 1;
                        canComplex(x - 1, y);
                        canComplex(x + 1, y);
                        return true;
                    }
                }
            }
            if (x != 0 && y != boardSize - 1) {
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0 && state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0) {  // left-down
                    if (hasLiberty(x - 1, y) || hasLiberty(x, y + 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x - 1][y] = 1;
                        checked[x][y + 1] = 1;
                        canComplex(x - 1, y);
                        canComplex(x, y + 1);
                        return true;
                    }
                }
            }
            if (x != 0 && y != 0) {
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0 && state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0) {  // left-up
                    if (hasLiberty(x - 1, y) || hasLiberty(x, y - 1)) {               // left-down
                        resetChecked();
                        return false;
                    } else {
                        checked[x - 1][y] = 1;
                        checked[x][y - 1] = 1;
                        canComplex(x - 1, y);
                        canComplex(x, y - 1);
                        return true;
                    }
                }
            }
            if (y != 0 && y != boardSize - 1) {
                if (state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0 && state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0) {  // up-down
                    if (hasLiberty(x, y - 1) || hasLiberty(x, y + 1)) {               // left-down
                        resetChecked();
                        return false;
                    } else {
                        checked[x][y + 1] = 1;
                        checked[x][y - 1] = 1;
                        canComplex(x, y + 1);
                        canComplex(x, y - 1);
                        return true;
                    }
                }
            }
            if (x != boardSize - 1 && y != 0) {
                if (state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0 && state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0) {  // right-up
                    if (hasLiberty(x, y - 1) || hasLiberty(x + 1, y)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x][y - 1] = 1;
                        checked[x + 1][y] = 1;
                        canComplex(x, y - 1);
                        canComplex(x + 1, y);
                        return true;
                    }
                }
            }
            if (x != boardSize - 1 && y != boardSize - 1) {
                if (state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0 && state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0) {  // left-up
                    if (hasLiberty(x + 1, y) || hasLiberty(x, y + 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x][y + 1] = 1;
                        checked[x + 1][y] = 1;
                        canComplex(x, y + 1);
                        canComplex(x + 1, y);
                        return true;
                    }
                }
            }
        }
        else if (sameNotCheckedCount(x, y) == 3) {
            if (x != 0 && y != 0 && y != boardSize) {
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0 && state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0 && state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0) {         // left-up-down          
                    if (hasLiberty(x - 1, y) || hasLiberty(x, y + 1) || hasLiberty(x, y - 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x - 1][y] = 1;
                        checked[x][y - 1] = 1;
                        checked[x][y + 1] = 1;
                        canComplex(x - 1, y);
                        canComplex(x, y - 1);
                        canComplex(x, y + 1);
                        return true;
                    }
                }
            }
            if (x != 0 && x != boardSize - 1 && y != 0) {
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0 && state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0 && state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0) {         // left-right-up   
                    if (hasLiberty(x - 1, y) || hasLiberty(x + 1, y) || hasLiberty(x, y - 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x - 1][y] = 1;
                        checked[x][y - 1] = 1;
                        checked[x + 1][y] = 1;
                        canComplex(x - 1, y);
                        canComplex(x, y - 1);
                        canComplex(x + 1, y);
                        return true;
                    }
                }
            }
            if (x != 0 && x != boardSize - 1 && y != boardSize - 1) {
                if (state[x - 1][y] == state[x][y] && checked[x - 1][y] == 0 && state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0 && state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0) {         // left-right-down
                    if (hasLiberty(x - 1, y) || hasLiberty(x, y + 1) || hasLiberty(x + 1, y)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x - 1][y] = 1;
                        checked[x + 1][y] = 1;
                        checked[x][y + 1] = 1;
                        canComplex(x - 1, y);
                        canComplex(x + 1, y);
                        canComplex(x, y + 1);
                        return true;
                    }
                }
            }
            if (x != boardSize - 1 && y != 0 && y != boardSize - 1) {
                if (state[x + 1][y] == state[x][y] && checked[x + 1][y] == 0 && state[x][y - 1] == state[x][y] && checked[x][y - 1] == 0 && state[x][y + 1] == state[x][y] && checked[x][y + 1] == 0) {         // left-up-down       
                    if (hasLiberty(x + 1, y) || hasLiberty(x, y + 1) || hasLiberty(x, y - 1)) {
                        resetChecked();
                        return false;
                    }
                    else {
                        checked[x + 1][y] = 1;
                        checked[x][y - 1] = 1;
                        checked[x][y + 1] = 1;
                        canComplex(x + 1, y);
                        canComplex(x, y - 1);
                        canComplex(x, y + 1);
                        return true;
                    }
                }
            }
        }
        else if (sameNotCheckedCount(x, y) == 4) {
            if (hasLiberty(x - 1, y) || hasLiberty(x + 1, y) || hasLiberty(x, y + 1) || hasLiberty(x, y - 1)) {
                resetChecked();
                return false;
            }
            else {
                checked[x - 1][y] = 1;
                checked[x + 1][y] = 1;
                checked[x][y - 1] = 1;
                checked[x][y + 1] = 1;
                canComplex(x - 1, y);
                canComplex(x + 1, y);
                canComplex(x, y - 1);
                canComplex(x, y + 1);
                return true;
            }
        }
    }
    return false;
}


void gameFunc::clearWrongChecked() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (checked[i][j] == 1 && hasLiberty(i, j)) {               // check if any stone that was marked as checked has any liberty
                checked[i][j] = 0;                                      // uncheck it
            }
        }
    }
}
// clears stones from checked array that have liberties

void gameFunc::changeCapturedToBlankBlack() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (checked[i][j] == 1 && state[i][j] == 2) {               // check if stone was checked and its color was white
                checked[i][j] = 0;                                      // uncheck it
                state[i][j] = 0;                                        // clear it from the board
                blackPrisoners++;                                       // add point for black
            }
        }
    }
}
// clear stone from the board and increment score of black player

void gameFunc::changeCapturedToBlankWhite() {
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (checked[i][j] == 1 && state[i][j] == 1) {               // check if stone was checked and its color was black
                checked[i][j] = 0;                                      // uncheck it
                state[i][j] = 0;                                        // clear it from the board
                whitePrisoners++;                                       // add point for black
            }
        }
    }
}
// clear stone from the board and increment score of black player

void gameFunc::complexCaptureBlack(int x, int y) {
    if (x != 0 && state[x - 1][y] == 2 && canComplex(x - 1, y)) changeCapturedToBlankBlack();               // check if you can capture on left
    if (x != boardSize - 1 && state[x + 1][y] == 2 && canComplex(x + 1, y)) changeCapturedToBlankBlack();   // check if you can capture on right
    if (y != boardSize - 1 && state[x][y + 1] == 2 && canComplex(x, y + 1)) changeCapturedToBlankBlack();   // check if you can capture on bottom
    if (y != 0 && state[x][y - 1] == 2 && canComplex(x, y - 1)) changeCapturedToBlankBlack();               // check if you can capture on top
}
// complex capture as black

void gameFunc::complexCaptureWhite(int x, int y) {
    if (x != 0 && state[x - 1][y] == 1 && canComplex(x - 1, y)) changeCapturedToBlankWhite();               // check if you can capture on left
    if (x != boardSize - 1 && state[x + 1][y] == 1 && canComplex(x + 1, y)) changeCapturedToBlankWhite();   // check if you can capture on right
    if (y != boardSize - 1 && state[x][y + 1] == 1 && canComplex(x, y + 1)) changeCapturedToBlankWhite();   // check if you can capture on bottom
    if (y != 0 && state[x][y - 1] == 1 && canComplex(x, y - 1)) changeCapturedToBlankWhite();               // check if you can capture on top
}
// complex capture as white

bool gameFunc::koRule(int x, int y) {
    if (clearSpot(x, y) == true && hasLiberty(x, y) == false && canEasyCapture(x, y)) {       // check if placement of stone can capture any stone
        return true;
    }
    return false;
}
// check if stone can capture other stones according to ko rule

bool gameFunc::adjacentSame(int x, int y) {
    return (state[x - 1][y] == state[x + 1][y]) && (state[x - 1][y] == state[x + 1][y]) &&
        (state[x - 1][y] == state[x + 1][y]) && (state[x - 1][y] == state[x + 1][y]) &&
        (state[x - 1][y] == state[x + 1][y]) && (state[x - 1][y] == state[x + 1][y]);
}
// checks if any of adjacent stones are same color

void gameFunc::runGame() {
    int zn = 0, x = startX + 1, y = startY + 1, back = 0, zero = 0;
    int posx, posy;
    char txt[32];

#ifndef __cplusplus
    Conio2_Init();
#endif
    // settitle sets the window title
    settitle("Jan, Pastucha, 193662");
    createState();
    createChecked();
    // hide the blinking cursor
    _setcursortype(_NOCURSOR);
    do {
        textbackground(BLACK);
        clrscr();

        sprintf(txt, "cursor: x: %d y: %d", x - startX, y - startY);
        gotoxy(legendX, 13);
        cputs(txt);
        gotoxy(startX, startY);
        drawLegend();
        drawBoard();
        drawGameState();
        // we draw a star
        gotoxy(x, y);

        // putch prints one character and moves the cursor to the right
        putch('*');
        // we wait for key press and get its code
        // most key codes correspond to the characters, like
        // a is 'a', 2 is '2', + is '+', but some special keys
        // like cursors provide two characters, where the first
        // one is zero, e.g., "up arrow" is zero and 'H'
        zero = 0;
        zn = getch();
        // we do not want the key 'H' to play role of "up arrow"
        // so we check if the first code is zero
        if (zn == 0) {
            zero = 1;		
            zn = getch();		
            if (zn == 0x48) {
                if (y - 1 > startY) {               // checks if y coordinate fits in borders
                    y--;
                }
            }
            else if (zn == 0x50) {
                if (y < startY + boardSize) {       // checks if y coordinate fits in borders
                    y++;
                }
            }
            else if (zn == 0x4b) {
                if (x - 1 > startX) {               // checks if x coordinate fits in borders
                    x--;
                }
            }
            else if (zn == 0x4d) {
                if (x < startX + boardSize) {       // checks if x coordinate fits in borders
                    x++;
                }
            }
        } // enter key is 0x0d or '\r'
        if (zn == 0x6e) {     // r key
            resetGame();
            x = startX + 1;
            y = startY + 1;
            if (turn() == 1) {
                swapTurn();
            }
        }
        else if (zn == 0x69 && approved == true) {  // i key
            posx = x - startX - 1;
            posy = y - startY - 1;
            if (turn() == 0 && clearSpot(posx, posy)) {
                if (koRule(posx, posy) && blockRepeatKo() == false) {
                    place(posx, posy, 1);
                    approved = false;
                    doneko = true;
                    put = true;
                }
                else if ((hasLiberty(posx, posy) == false && canComplex(posx, posy) && blockRepeatKo() == false) || hasLiberty(posx, posy)) {
                    place(posx, posy, 1);
                    approved = false;
                    doneko = false;
                    put = true;
                }
            }
            else if (turn() == 1 && clearSpot(posx, posy)) {
                if (koRule(posx, posy) && blockRepeatKo() == false) {
                    place(posx, posy, 2);
                    approved = false;
                    doneko = true;
                    put = true;
                }
                else if ((hasLiberty(posx, posy) == false && canComplex(posx, posy) && blockRepeatKo() == false) || hasLiberty(posx, posy)) {
                    place(posx, posy, 2);
                    approved = false;
                    doneko = false;
                    put = true;
                }
            }
        }
        else if (zn == 0x0d && put == true) {   // enter key
            gamestarted = true;
            if (turn() == 0) {
                if (koRule(posx, posy) && blockRepeatKo() == false) {
                    place(posx, posy, 1);
                    captureBasic(posx, posy);
                    swapTurn();
                    approved = true;
                    put = false;
                }
                else if ((hasLiberty(posx, posy) == false && canComplex(posx, posy)) || hasLiberty(posx, posy)) {
                    place(posx, posy, 1);
                    captureBasic(posx, posy);
                    complexCaptureBlack(posx, posy);
                    swapTurn();
                    approved = true;
                    put = false;
                }
            }
            else if (turn() == 1) {
                if (koRule(posx, posy) && blockRepeatKo() == false) {
                    place(posx, posy, 2);
                    captureBasic(posx, posy);
                    swapTurn();
                    approved = true;
                    put = false;
                }
                else if ((hasLiberty(posx, posy) == false && canComplex(posx, posy)) || hasLiberty(posx, posy)) {
                    place(posx, posy, 2);
                    captureBasic(posx, posy);
                    complexCaptureWhite(posx, posy);
                    swapTurn();
                    approved = true;
                    put = false;
                }
            }
        }
        else if (zn == 0x1b && approved == false) { // escape
            x = posx + startX + 1;
            y = posy + startY + 1;
            place(posx, posy, 0);
            approved = true;
        }
        else if (zn == 0x68 && gamestarted == false) { // h key
            posx = x - startX - 1;
            posy = y - startY - 1;
            if (clearSpot(posx, posy)) {
                place(posx, posy, 1);
                komi += 6;
            }
        }
    } while (zn != 'q');
    _setcursortype(_NORMALCURSOR);

    for (int i = 0; i < boardSize; i++)
        free(state[i]);
    free(state);

    for (int i = 0; i < boardSize; i++)
        free(checked[i]);
    free(checked);
}
// start game and handle all functions