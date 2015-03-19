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
    
    p.up();
    sleep(1);
    p.down();
    sleep(1);
    p.down();
    p.down();
    sleep(1);
    p.up();
    sleep(1);
    // just return 1 or 2 at random for now
    srandom( (int)time(NULL) );
    return (random() % 2) + 1;
}






