#ifndef PONG_UTIL_H
#define PONG_UTIL_H

#include <curses.h>


/* Constants for the Ball */
#define BALL_START_X (COLS / 2)
#define BALL_START_Y (LINES / 2)
#define BALL_SPEED_MAX (50)          // lower numbers are faster
#define BALL_SPEED_MIN (100)         
#define BALL_UPDATE_INTERVAL 500000
#define BALL_SPEED_MODIFIER 10



#define PADDLE_START_TOP ((LINES / 3) + 1)

#define TOP_WALL_OFFSET 1
#define BOTTOM_WALL_OFFSET 3
#define VERT_WALL_OFFSET 3

#define SCORE_MAX 5

void fatal_error(const char *s);
void quit();
void pause();
int printToScreen(const char *str, int x, int y);




#endif // PONG_ERRORS_H

