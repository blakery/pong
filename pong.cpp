#include <curses.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"
#include "definitions.h"


#include <stdlib.h>
#include <unistd.h>
#include <time.h>


void play();
int round();
void quit();

int main() {
    play();
    return 0;
}



void play() {
    int p1Score = 0;
    int p2Score = 0;
    Court *court = new Court();    

    while(p1Score < SCORE_MAX && p2Score < SCORE_MAX) {
        sleep(1);

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
    Paddle p;
    int score;
    
    b.serve();
    while( !(score = b.move_ball(&p, NULL)) ) {
        char ch=getch();
        b.set_move(); // FIXME: implement timer
        /*switch (ch) {
            case 'q': quit(); break;
            case 'w': p.up(); break;
            case 's': p.down(); break;
            
            case KEY_UP: p.up(); break;
            case KEY_DOWN: p.down(); break;
            default:;
        }*/
    }
 //   srandom( (int)time(NULL) );
    return score;
}



// FIXME: this should eventually prompt
void quit() {
    endwin();
    exit(0);

}

