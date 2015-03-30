#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <curses.h>
#include "pong_util.h"
#include "ball.h"
#include "paddle.h"




#define BALL_CHAR '*'

// definitions for static data members
int Ball::x_move;
int Ball::y_move; 
timer_t Ball::timerid;
struct itimerspec Ball::itimer;
struct timespec Ball::interval;




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
    disable_timer(); 
    draw(BALL_START_X, BALL_START_Y);
    refresh();

}




void Ball::serve() {
    draw(BALL_START_X, BALL_START_Y);
    srandom( (int)time(NULL) );
    
    x_speed = random() % BALL_SPEED_MIN;
    y_speed = random() % BALL_SPEED_MIN;

    // This looks counter-intuitive, but note that lowe numbers are higher
    if(x_speed < BALL_SPEED_MAX ) { x_speed = BALL_SPEED_MAX; }
    if(y_speed < BALL_SPEED_MAX ) { y_speed = BALL_SPEED_MAX; }
    
    // make sure the ball always serves towards a player
    if(x_speed > y_speed) {
        int tmp = x_speed;
        x_speed = y_speed;
        y_speed = x_speed;
    }
    // randomize + or - for direction
    if(random() % 2) { x_dir *= -1; }
    if(random() % 2) { y_dir *= -1; }    

    set_timer(); 
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





/* static void Ball::set_move(int signal)
 * Called by the timer signal. The parameter 'signal' is ignored.
 * Declared static for ease of signal handling.
 */
void Ball::set_move(int signal) {
    x_move++; 
    y_move++; 
}





/* int Ball::move_ball(Paddle *left_paddle, Paddle *right_paddle)
 * Returns: 1 if player 1 has scored, 2 if player 2 has scored, 0 otherwise
 */
int Ball::move_ball(Paddle *left_paddle, Paddle *right_paddle) {         
        int x = x_loc;
        int y = y_loc;

        if(x_move > x_speed) {
            x += x_dir;
            x_move = 0;

            int score = checkLeftBounce(left_paddle)
                      + checkRightBounce(right_paddle);
            if(score) { return score;
            } else { draw(x, y);
            }
        }  
        if(y_move > y_speed) {
            y += y_dir;
            y_move = 0;
            draw(x, y);
            checkYBounce();
        } 

        return 0;
}

    



/* void Ball::checkYBounce()
 * checks to see of the ball has bounced off of the top or bottom walls
 */
void Ball::checkYBounce() {
    int lines = (getmaxy(curscr);

    // FIXME: the <= and >=, rather than == simply hide a bug where
    //        the ball can go past the wall. while this is preferable to
    //        the bug being obvious, it should still be fixed.
    // NOTE: this is probably something else, since it's still happening.
    //       some possibilities: - a race condition somewhere,
    //              - interaction in corners / near both the side and a paddle
    //              - a problem with the paddles somewhere
    if( (y_loc <= TOP_WALL_OFFSET+1 )
        ||  (y_loc >= lines - BOTTOM_WALL_OFFSET)-1) ) {
        y_dir = y_dir * (-1);
    }
}


/* int Ball::checkLeftBounce(Paddle *p)
 * bounce() helper
 * bounces the ball if it has contacted the left paddle
 * if paddle is NULL, will bounce the ball if it has hit the left side
 *     otherwise, it will score if the ball hits.
 * returns 1 if the ball has scored on the left side, 0 if not.
 */
int Ball::checkLeftBounce(Paddle *p) {
        // FIXME: see bug in Ball::checkYBounce()
    if(p) {
        // if a paddle is in play, score if it hits the wall 
        if(x_loc <= VERT_WALL_OFFSET+1) { return 1;
        // bounce if the ball hits the paddle
        } else if(p->contact(x_loc, y_loc) >= 1) {
            x_dir = x_dir * (-1);
            return 0;
        }
    } else if(x_loc <= VERT_WALL_OFFSET+1) {
        x_dir =  x_dir * (-1);
        return 0;
    } else return 0;
}



/* int Ball::checkRightBounce(Paddle *p) 
 * bounce() helper
 * bounces the ball if it has contacted the right paddle
 * if paddle is NULL, will bounce the ball if it has hit the right side
 *     otherwise, it will score if the ball hits.
 * returns 2 if the ball has scored 0 if not.
 */
int Ball::checkRightBounce(Paddle *p) {
    // FIXME: see bug in Ball::bounce()
    int cols = getmaxx(curscr);
    
    if(p) {
        // hit a defended wall => score
        if(x_loc <=  cols - (VERT_WALL_OFFSET+1) ) { return 2;
        // hit a paddle => bounce
        } else if(p->contact(x_loc, y_loc) >= 1) {
            x_dir =  x_dir * (-1);
            return 0;
        }
    } else if(x_loc <= cols - (VERT_WALL_OFFSET+1) ) {
        // hit an undefended wall => bounce
        x_dir =  x_dir * (-1);
        return 0;
    } else return 0;
}



void Ball::alterSpeed() {
    //FIXME: alter so that the collision plane can be specified, 
    //       and bounce changed accordingly
    //       also possibly have the total speed decrease slightly with each 
    //       non-paddle bounce
    srandom( (int)time(NULL) );
    
    x_speed += (random() % BALL_SPEED_MODIFIER) % BALL_SPEED_MIN;
    if(x_speed < BALL_SPEED_MAX) { x_speed = BALL_SPEED_MAX; }
    
    y_speed += (random() % BALL_SPEED_MODIFIER) % BALL_SPEED_MIN;
    if(y_speed < BALL_SPEED_MAX) { y_speed = BALL_SPEED_MAX; }    
}



/* ******************************************************
                Timer Functions
********************************************************* */

void set_signal(struct sigevent *);

void Ball::set_timer() {
    struct sigevent signal;

    if(!timerid) {     
        set_signal(&signal);

        if(timer_create(CLOCK_REALTIME, &signal, &timerid)) {
            fatal_error("Could not create timer");
        }
    }
    enable_timer();
}



void set_signal(struct sigevent *signal) {
    struct sigaction action;

    action.sa_handler = &Ball::set_move;
    if( sigaction(SIGALRM, &action, NULL) ) {
        fatal_error("Unable to set timer signal handler");
    }

    signal->sigev_notify = SIGEV_SIGNAL;
    signal->sigev_signo = SIGALRM;
}



void Ball::enable_timer() {
    int flags = 0;
    interval.tv_sec = 0;
    interval.tv_nsec = BALL_UPDATE_INTERVAL;
    
    itimer.it_interval = interval;
    itimer.it_value = interval;

    if( timer_settime(timerid, flags, &itimer, NULL) ) { 
        fatal_error("Unable to set timer");
    }

}


void Ball::disable_timer() {
    struct itimerspec temp;
    struct timespec nil_time;
    nil_time.tv_sec = nil_time.tv_nsec = 0;
    temp.it_interval = nil_time;
    temp.it_value = nil_time;

    if( timer_settime(timerid, 0, &temp, NULL) ) { 
        fatal_error("Unable to stop timer");
    }

}

