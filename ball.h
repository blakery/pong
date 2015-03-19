
//class Tuple;


class Ball {

public:
    Ball();
    void move_ball();
    void serve();

  //  Tuple location();
    //Tuple direction();

private:
    int x_loc;
    int y_loc;
    int x_move;
    int y_move;  
    void draw(int, int);
};
