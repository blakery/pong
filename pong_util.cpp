#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h> 
#include <ncurses.h>
#include "pong_util.h"







void fatal_error(const char *s) {
    endwin();
    perror(s);
    exit(-1);
}


/* void quit()
 * used for voluntary, user requested exits.
 * FIXME: this should eventually prompt
 */
void quit() {
    endwin();
    exit(0);
}



void pause() {
    int pause_y = LINES/2;
    int pause_x = (COLS/2) - VERT_WALL_OFFSET;

    printToScreen("PAUSE", pause_x, pause_y);
    while(TRUE) {
        char ch = getch();
        switch (ch) {
            case 'p': 
                printToScreen("     ",pause_x, pause_y);
                return;
            case 'q': quit();
            default:;
        }
    }
}



// returns the new position of x
int printToScreen(const char *str, int x, int y) {
    

    for(int i=0; i < strlen(str); i++) {
        move(y, x++);
        addch(str[i]);
    }
    return x;
}