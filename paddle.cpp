#include <curses.h>
#include "definitions.h"
#include "paddle.h"

#define PADDLE_CHAR ACS_VLINE

Paddle::Paddle() {
    paddle_length = 3;
    paddle_top = PADDLE_START_TOP;
    // FIXME: add the ability to specify which paddle, and have the 
    //        axis change to match
    paddle_axis = VERT_WALL_OFFSET + 2;
    
    draw();
}

Paddle::~Paddle() {
    reset();

}

void Paddle::up() {
    
    if( (paddle_top + paddle_length) < BOTTOM_WALL_OFFSET) {
        erase();
        paddle_top++;
        draw();
    }
    

}


void Paddle::down() {

    if( (paddle_top) > TOP_WALL_OFFSET) {
        erase();
        paddle_top--;
        draw();
    }
    

}

void Paddle::reset() {
    erase();
    paddle_top = PADDLE_START_TOP;
    draw();

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
 //   refresh();
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
 * at some point positive or negative, or the magnitude of the number
 * may become significant in, but not yet.
 */
int Paddle::contact(int x, int y) {


    return 0;
}
