#ifndef AI_PADDLE_H
#define AI_PADDLE_H

#include "paddle.h"
#define PADDLE_DEFAULT_DELAY 500

class Ball;
 
class AIPaddle: public Paddle {

    public:
        AIPaddle(int axis): Paddle(axis) {
            delay_count = 0;
            delay = PADDLE_DEFAULT_DELAY;
        }  
        AIPaddle(int axis, int d): Paddle(axis) {
            delay_count = 0;
            delay = d;
        }
        void update(Ball *);

    private: 
        int delay;
        int delay_count;
};




#endif  // end AI_PADDLE_H
