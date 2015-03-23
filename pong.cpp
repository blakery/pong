#include <stdlib.h>
//#include <unistd.h>
#include <curses.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"
#include "pong_util.h"




void play();
int round();



int main() {
    play();
    return 0;
}



void play() {
    int p1Score = 0;
    int p2Score = 0;
    Court *court = new Court();    

    while(p1Score < SCORE_MAX && p2Score < SCORE_MAX) {
        int player = round();

        if(player == 1) { p1Score++; 
        } else if(player == 2) { p2Score++; 
        }
        court->drawScore(p1Score, p2Score);  
    }
}


/* int round()
 * returns: 
 *      0 if no player scored (can't happen atm)
 *      1 if player 1 scored
 *      2 if player 2 scored
 */
int round() {
    Ball b;
    Paddle p1;// = new Paddle(1); 
   // Paddle *p2;// = NULL;// = new Paddle(2); 
    int score = 0;
    
    b.serve();
    while( !(score) ) {
        char ch=getch();

        switch (ch) {
            case 'q': quit(); break; // this could return
            case 'w': 
                p1.up(); 
                b.checkPaddleBounce(&p1, (Paddle *) NULL);
                break;
            case 's': 
                p1.down();
                b.checkPaddleBounce(&p1, (Paddle *) NULL);
                break;     
            case 'p':
                pause();
                break;     
            default: score = b.move_ball(&p1, NULL);
        }
        b.set_move(0);
    }
    return score;
}





