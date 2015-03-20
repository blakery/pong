
class Paddle;

class Ball {

public:
    Ball();
    ~Ball();
    void serve();
    void set_move();
    int move_ball(Paddle *, Paddle *);


    int get_x_location();
    int get_y_location();
    //int get_x_direction();
    //int get_y_direction();
    int score();

private:
    int x_loc;
    int y_loc;
    int x_move;
    int y_move;
    int x_speed;
    int y_speed;
    int x_dir;
    int y_dir;
    void draw(int, int);
    int bounce(Paddle *, Paddle *);
};
