#ifndef COURT_H
#define COURT_H

/* class Court 
 * The pong court
 * Initializes the ncurses library, and draws the court walls, with the
 *     score set to "0 - 0"
 * Contains drawScore(), to draw the score at the bottom right of the court
 */
class Court {

public: 
    Court();
    void drawScore(int, int);

private:
    void drawLines();
};



#endif //COURT_H
