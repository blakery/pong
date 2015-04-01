#ifndef AI_PADDLE_H
#define AI_PADDLE_H

#include "paddle.h"

class Ball;
 
class AIPaddle: public Paddle {

    public:
        AIPaddle(int axis): Paddle(axis){}  
        void update(Ball *);

};




#endif  // end AI_PADDLE_H
