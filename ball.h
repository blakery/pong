#ifndef BALL_H
#define BALL_H
#include <time.h>

class Paddle;

class Ball {

public:
    Ball();
    ~Ball();
    void serve();
    int move_ball(Paddle *, Paddle *);
    int score();
    void set_timer();
    static void set_move(int);    
    void checkPaddleBounce(Paddle *left_paddle, Paddle *right_paddle);

    
private:
    int x_loc;
    int y_loc;

    int x_speed;
    int y_speed;
    int x_dir;
    int y_dir;   
    
    void draw(int, int);
    int bounce(Paddle *, Paddle *);
    void checkYBounce();
    int checkLeftBounce(Paddle *);
    int checkRightBounce(Paddle *);
    
    void alterSpeed();
    
    void enable_timer();
    void disable_timer();    

    static int x_move;
    static int y_move; 

    static timer_t timerid;
    static struct itimerspec itimer;
    static struct timespec interval;
};



#endif // BALL_H

