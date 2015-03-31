#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include "ball.h"
#include "paddle.h"
#include "court.h"
#include "pong_util.h"
#include "aipaddle.h"



void play(int);
int round(Paddle *, AIPaddle *);
void endOfGame(int, int);


int main() {
    play(1);
    return 0;
}



void play(int nPlayers) {
    int p1Score = 0;
    int p2Score = 0;
    Paddle *p1 = NULL;
    AIPaddle *p2 = NULL;
    
    Court *court = new Court();    
/*
    if(nPlayers >= 1) { }
    if(nPlayers == 2) { p2 = new Paddle(2); 
    }*/
    p1 = new Paddle(1); 
    p2 = new AIPaddle(2);

    while(p1Score < SCORE_MAX && p2Score < SCORE_MAX) {
        int player = round(p1, p2);

        if(player == 2) { p1Score++; 
        } else if(player == 1) { p2Score++; 
        }
        court->drawScore(p1Score, p2Score);  
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
    printToScreen("Play again? y/n", x, y + 1);

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
                exit(0);
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
int round(Paddle *p1, AIPaddle *p2) {
    Ball b;
    int score = 0;
    char ch;

    // Wait for a key to be pressed (a paddle movement key or the spacebar)
    while(TRUE) {
        ch=getch();
        if(ch == 'w' || ch == 's' || ch == 'i' || ch == 'k' || ch == ' ') { 
           b.serve();               
           break; 
        } else if(ch == 'q') { 
            quit();
        }
    }

    while( !(score) ) {
        ch = getch();
        switch (ch) {
            case 'q': quit(); // Note: this could return (quit() propts)         
                break;
            case 'p': pause();
                break;                   
            case 'w': if(p1) p1->up(); 
                break;
            case 's': if(p1) p1->down();
                break;
            case 'i': if(p2) p2->up(); 
                break; 
            case 'k': if(p2) p2->down();
                break;   
            default: p2->update(&b);;
                
        }  
        score = b.move_ball(p1, p2);
    }
    return score;
}



