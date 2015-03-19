#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "definitions.h"
#include "ball.h"

#include <stdio.h>

#define BALL_CHAR '*'



Ball::Ball() {
    x_loc = BALL_START_X;
    y_loc = BALL_START_Y;
    
    draw(x_loc, y_loc);

}


void Ball::move_ball() {
    x_loc += x_move;
    y_loc += y_move;

}



void Ball::serve() {
    srandom( (int)time(NULL) );
    x_move = random() % SPEED_MAX;
    y_move = random() % SPEED_MAX;
    // randomize + or -
    if(random() % 2) { x_move *= -1; }
    if(random() % 2) { y_move *= -1; }    

}


void Ball::draw(int x, int y) {
    
    move(y, x);
    addch(BALL_CHAR);
    refresh();
}
