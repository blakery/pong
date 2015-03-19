#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "definitions.h"
#include "court.h"



#define VERT_WALL_CHAR ('|')
#define HORZ_WALL_CHAR ('_')


Court::Court() {
    initscr();
    drawLines();
    drawScore(0, 0);
    refresh();
}



void Court::drawScore(int p1, int p2) {
    int y = LINES-2;
    int x = COLS - 15;
    char str[256];

    sprintf(str, "SCORE: %d - %d", p1, p2);
    x = printToScreen( (const char *)str, x, y);
}


// returns the new position of x
int Court::printToScreen(const char *str, int x, int y) {
    
    for(int i=0; i < strlen(str); i++) {
        move(y, x++);
        addch(str[i]);
    }
    return x;
}





/* void Court::drawLines()
 * draws the four walls of the court
 */
void drawTopLine();
void drawBottomLine();
void drawLeftLine();
void drawRightLine();

void Court::drawLines(){

    drawTopLine();
    drawBottomLine();
    drawLeftLine();
    drawRightLine();
    
}


void drawTopLine() {
    int y = 0 + TOP_WALL_OFFSET;
    
    for(int x=VERT_WALL_OFFSET; x < (COLS - VERT_WALL_OFFSET); x++) {
        move(y, x);
        addch(HORZ_WALL_CHAR);
    }
    
}


void drawBottomLine() {
    int y = LINES - BOTTOM_WALL_OFFSET;
    
    for(int x=VERT_WALL_OFFSET; x < (COLS - VERT_WALL_OFFSET); x++) {
        move(y, x);
        addch(HORZ_WALL_CHAR);
    }
}


void drawLeftLine() {
    int x = 0 + VERT_WALL_OFFSET;

    for(int y=TOP_WALL_OFFSET+1; y < LINES - BOTTOM_WALL_OFFSET+1; y++) {
        move(y, x);
        addch(VERT_WALL_CHAR);
    }
}


void drawRightLine() {
    int x = COLS - VERT_WALL_OFFSET;
    
    for(int y=TOP_WALL_OFFSET+1; y < LINES - BOTTOM_WALL_OFFSET+1; y++) {
        move(y, x);
        addch(VERT_WALL_CHAR);
    }
}

