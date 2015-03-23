#include <curses.h>
#include "definitions.h"
#include "paddle.h"

#define PADDLE_CHAR ACS_VLINE

Paddle::Paddle() {

    paddle_length = 3;
    paddle_top = PADDLE_START_TOP;
    paddle_axis = VERT_WALL_OFFSET + 2;
    
    draw();
}

Paddle::Paddle(int side) {
    paddle_length = 3;
    paddle_top = PADDLE_START_TOP;

    if(side == 1) {
        paddle_axis = VERT_WALL_OFFSET + 2;
    } else if(side == 2) {
        paddle_axis = COLS - (VERT_WALL_OFFSET + 2);
    } else {
        paddle_axis = VERT_WALL_OFFSET + 2;
    }
    draw();
}

Paddle::~Paddle() {
    erase();

}


void Paddle::reset() {
    erase();
    paddle_top = PADDLE_START_TOP;
    draw();

}

void Paddle::up() {  
    if( paddle_top > TOP_WALL_OFFSET+1) {
        erase();
        paddle_top--;
        draw();
    }
}


void Paddle::down() {

    if( (paddle_top + paddle_length) < LINES - BOTTOM_WALL_OFFSET) {
        erase();
        paddle_top++;
        draw();
    } 
}



/* void Paddle::erase() 
 * should be called before envoking draw and before setting the paddle to
 *      it's new position.
 * doesn't refresh the screen, but overwrites the current location
 * of the paddle with empty spaces 
 */
void Paddle::erase() {
    int x = paddle_axis;
    int y = paddle_top;
    
    for(int i=0; i<paddle_length; i++) {
        move(y+i, x);
        addch(' ');
    }
}


void Paddle::draw() {
    int x = paddle_axis;
    int y = paddle_top;
    
    for(int i=0; i<paddle_length; i++) {
        move(y+i, x);
        addch(PADDLE_CHAR);
    }
    refresh();
}

/* int Paddle::contact(int x, int y)
 * returns non-zero if (x, y) are in contact with the paddle.
 * returns -1 if the ball is inside the paddle (same x and y as a paddle char)
 * at some point the magnitude of the number
 * may become significant in, but not yet.
 */
int Paddle::contact(int x, int y) {
    if(x == paddle_axis) {
        if(y > paddle_top && y < paddle_top + paddle_length) {
            return -1;
        } else if (y == paddle_top-1) { return 1;
        } else if (y == paddle_top + paddle_length + 1) { return 1;
        } else { return 0;
        }
    } else if(x == paddle_axis + 1 || x == paddle_axis - 1) {
        if(y > paddle_top && y < paddle_top + paddle_length) {
            return 1;
        } else { return 0;
        }
    } else { return 0;
    }
}


