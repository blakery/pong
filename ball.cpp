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
    x_move =0;
    y_move=0;
    x_speed=0;
    y_speed=0;
    y_dir=1;
    x_dir=1;
    
    draw(BALL_START_X, BALL_START_Y);
}

Ball::~Ball() {
    move(y_loc, x_loc);
    addch(' ');
    refresh();
}


void Ball::serve() {
    srandom( (int)time(NULL) );
    
    x_speed = random() % SPEED_MIN;
    y_speed = random() % SPEED_MIN;

    if(x_speed < SPEED_MAX ) { x_speed = SPEED_MAX; }
    if(y_speed < SPEED_MAX ) { y_speed = SPEED_MAX; }

    x_speed = SPEED_MIN;
    y_speed = SPEED_MIN;
    
    // make sure the ball always serves towards a player
    if(x_speed > y_speed) {
        int tmp = x_speed;
        x_speed = y_speed;
        y_speed = x_speed;
    }
    // randomize + or - direction
    if(random() % 2) { x_dir *= -1; }
    if(random() % 2) { y_dir *= -1; }    

}


void Ball::set_move() {
    x_move++; 
    y_move++; 
}


void Ball::move_ball() {    
    
    if(x_move < x_speed && y_move < y_speed) { return; }
    if(x_move >= x_speed) {
        draw(x_loc + x_dir, y_loc);
        x_move = 0;
    }  
    if(y_move >= y_speed) {
        draw(x_loc, y_loc + y_dir);
        y_move = 0;
    }
        bounce();    
}




int Ball::get_x_location() {
    return x_loc;
}
int Ball::get_y_location() {
    return y_loc;    
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


void Ball::bounce() {
    if( (y_loc == TOP_WALL_OFFSET+1) 
    ||  (y_loc == (LINES - BOTTOM_WALL_OFFSET)-1) ) {
        y_dir *= -1;
    }
    
    if( (x_loc == VERT_WALL_OFFSET+1) 
    ||  (x_loc == COLS - (VERT_WALL_OFFSET+1)) ) {
        x_dir *= -1;
    }
}
