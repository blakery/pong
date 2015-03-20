#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "definitions.h"
#include "ball.h"

#include <stdio.h>

#define BALL_CHAR '*'



Ball::Ball() {
    draw(BALL_START_X, BALL_START_Y);

}

/*
void Ball::increment() {
    
    x_move += x_speed;
    y_move += y_speed;

}
*/

void Ball::move_ball() {
    draw(x_loc + x_move, y_loc + y_move);
    x_move = 0;
    y_move = 0;
}



void Ball::serve() {
    srandom( (int)time(NULL) );
    x_speed = random() % SPEED_MAX;
    y_speed = random() % SPEED_MAX;
    // randomize + or -
    if(random() % 2) { x_move *= -1; }
    if(random() % 2) { y_move *= -1; }    

}


/* void Ball::draw(int x, int y)
 * Erases the ball at its old corrdinates and draws it at the new ones.
 * Then sets the ball's location to the new location that was passed.
 * THIS IS THE ONLY PLACE THE BALL'S LOCATION SHOULD EVER BE CHANGED!
 */
void Ball::draw(int x, int y) {
    move(y_loc, x_loc);
    addch(' ');
    
    move(y, x);
    addch(BALL_CHAR);
    x_loc = x;
    y_loc = y;
    refresh();
}


int Ball::get_x_location() {
    return x_loc;
}
int Ball::get_y_location() {
    return y_loc;    
}
