#include <stdlib.h>
//#include <unistd.h>
#include <curses.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"
#include "pong_util.h"




void play(int);
int round(Paddle *, Paddle *);



int main() {
    play(1);
    return 0;
}



void play(int nPlayers) {
    int p1Score = 0;
    int p2Score = 0;
    Paddle *p1 = NULL;
    Paddle *p2 = NULL;
    
    Court *court = new Court();    

    if(nPlayers >= 1) { p1 = new Paddle(1); }
    if(nPlayers == 2) { p2 = new Paddle(2); }

    while(p1Score < SCORE_MAX && p2Score < SCORE_MAX) {
        int player = round(p1, p2);

        if(player == 1) { p1Score++; 
        } else if(player == 2) { p2Score++; 
        }
        court->drawScore(p1Score, p2Score);  
    }
    endwin();
}


/* int round()
 * returns: 
 *      0 if no player scored (can't happen atm)
 *      1 if player 1 scored
 *      2 if player 2 scored
 */
int round(Paddle *p1, Paddle *p2) {
    Ball b;
    int score = 0;
    
    b.serve();
    while( !(score) ) {
        char ch=getch();

        switch (ch) {
            case 'q': // this could return
                quit();         
                break; 
            case 'w': 
                p1->up(); 
                b.checkPaddleBounce(p1, p2);
                break;
            case 's': 
                p1->down();
                b.checkPaddleBounce(p1, p2);
                break;     
            case 'p':
                pause();
                break;     
            default: score = b.move_ball(p1, p2);
        }
    }
    return score;
}



