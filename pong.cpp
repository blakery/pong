#include <curses.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"
#include "definitions.h"


void play();
void round();


int main() {
    play();
    return 0;
}




void play() {
    int p1Score = 0;
    int p2Score = 0;
    Court court;    

    while(p1Score < SCORE_MAX && p2Score < SCORE_MAX) {
        round();
        court.drawScore(p1Score, p2Score);    
    }
        
}




void round() {
    Ball b;
    Paddle p;

}






