#ifndef PADDLE_H
#define PADDLE_H

class Paddle {

public:
    Paddle();
    Paddle(int side);    
    ~Paddle();
    void up();
    void down();
    void reset();
    int contact(int x, int y);
    void erase();

protected: 
    int paddle_top;
    int paddle_axis;

    // this may be custumizable at some point, for difficulty level
    int paddle_length;
    void draw();

};


#endif
