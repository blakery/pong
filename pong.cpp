#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
#include <curses.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"
#include "pong_util.h"




void play(int);
int round(Paddle *, Paddle *);
void endOfGame(int, int);


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
        char ch;
        while( !(ch=getch()) ) {;}
    }
    endOfGame(p1Score, p2Score);
}


void endOfGame(int p1Score, int p2Score) {
    const char *winner;
    int points;
    char message[24];
    
    if(p1Score > p2Score) { 
        winner = "Player 1";
        points = p1Score;
    } else { 
        winner = "Player 2";
        points = p2Score;
    }
    
    sprintf(message, "%s won with %d points.", winner, points);
    int y = getmaxy(curscr) /3;
    int x = getmaxx(curscr) / 3;
    printToScreen(message, x, y);
    sprintf(message, "Play again? y/n");
    printToScreen(message, x, y + 1);

    while(TRUE) {
        char ch = getch();
        switch (ch) {
            case 'y': 
                printToScreen("                        ", x, y);
                printToScreen("                        ", x, y+1);
                play(1);
                return;
            case 'n':
                endwin();
                return;
            default:;
        }
    }
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
    char ch;

    while( !(ch=getch()) ) {
    }
    b.serve();    
    while( !(score) ) {
        ch = getch();

        switch (ch) {
            case 'q': 
                quit(); // Note: this could return (quit() propts)         
                break; 
            case 'w': 
                p1->up(); 
                break;
            case 's': 
                p1->down();
                break;     
            case 'p':
                pause();
                break;     
            default: score = b.move_ball(p1, p2);
        }
    }
    return score;
}



