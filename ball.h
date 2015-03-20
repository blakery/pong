



class Ball {

public:
    Ball();
    void move_ball();
    void serve();

    int get_x_location();
    int get_y_location();
    //Tuple direction();
    int score();
    
private:
    int x_loc;
    int y_loc;
    int x_move;
    int y_move;
    int x_speed;
    int y_speed;
    void draw(int, int);
};
