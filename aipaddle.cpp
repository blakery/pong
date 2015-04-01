#include "aipaddle.h"
#include "ball.h"
#include "curses.h"
#include "paddle.h"




/* void AIPaddle::update(Ball *b)
 * Update the paddle's position for an automated opponent
 * If the paddle is not on the same axis as the ball, move it in 
 * the direction of the ball
 */
void AIPaddle::update(Ball *b) {
    int half_court = getmaxx(curscr) / 2;
    
    if(delay_count++ < delay) { return;
    // only move if the ball is on this half of the court
    } else if(b->x() < paddle_axis  &&  b->x() < half_court) { return;
    } else if(b->x() > paddle_axis  &&  b->x() > half_court) { return;
    } else if( b->y() < paddle_top ) { up();
    } else if (b->y() > (paddle_top + paddle_length) ){ down();
    }
    delay_count=0;

}

