#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "pong_util.h"
#include "court.h"



#define VERT_WALL_CHAR ACS_VLINE
#define HORZ_WALL_CHAR ACS_HLINE


Court::Court() {
    
    initscr();   // initialize ncurses
    noecho();    // don't echo typed characters
    curs_set(0); // don't show blinking cursor
   // cbreak();    // don't wait for return key
    nodelay(stdscr, TRUE);  // don't block
    drawLines();

    drawScore(0, 0);

}



void Court::drawScore(int p1, int p2) {
    int y = getmaxy(curscr)-2;
    int x = getmaxx(curscr) - 15;
    char str[256];

    sprintf(str, "SCORE: %d - %d", p1, p2);
  //  move(y, x);
//    addchstr( (const char *) &str);
    x = printToScreen( (const char *)str, x, y);
    refresh();
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
    refresh();
}


void drawTopLine() {
    int y = 0 + TOP_WALL_OFFSET;
    
    for(int x=VERT_WALL_OFFSET; x < (getmaxx(curscr) - VERT_WALL_OFFSET); x++) {
        move(y, x);
        addch(HORZ_WALL_CHAR);
    }
    
}


void drawBottomLine() {
    int y = getmaxy(curscr) - BOTTOM_WALL_OFFSET;
    
    for(int x=VERT_WALL_OFFSET; x < (getmaxx(curscr) - VERT_WALL_OFFSET); x++) {
        move(y, x);
        addch(HORZ_WALL_CHAR);
    }
}


void drawLeftLine() {
    int x = 0 + VERT_WALL_OFFSET;
    
    for(int y=TOP_WALL_OFFSET+1; y < getmaxy(curscr) - BOTTOM_WALL_OFFSET; y++) {
        move(y, x);
        addch(VERT_WALL_CHAR);
    }
    move(TOP_WALL_OFFSET, x);
    addch(ACS_ULCORNER);    
    move(getmaxy(curscr)-BOTTOM_WALL_OFFSET, x);
    addch(ACS_LLCORNER);   
}


void drawRightLine() {
    int x = getmaxx(curscr) - VERT_WALL_OFFSET;

    for(int y=TOP_WALL_OFFSET+1; y < getmaxy(curscr) - BOTTOM_WALL_OFFSET; y++) {
        move(y, x);
        addch(VERT_WALL_CHAR);
    }
    move(TOP_WALL_OFFSET, x);
    addch(ACS_URCORNER);    
    move(getmaxy(curscr)-BOTTOM_WALL_OFFSET, x);
    addch(ACS_LRCORNER);
}

