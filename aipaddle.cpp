#include "aipaddle.h"
#include "ball.h"
#include "paddle.h"




/* void AIPaddle::update(Ball *b)
 * Update the paddle's position for an automated opponent
 * If the paddle is not on the same axis as the ball, move it in 
 * the direction of the ball
 */
void AIPaddle::update(Ball *b) {
    
    if( b->y() < paddle_top ) {
        up();
    } else if (b->y() > (paddle_top + paddle_length) ){
        down();
    }
    

}

