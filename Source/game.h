#include <stdbool.h>
#include <stdlib.h>
extern  int MAX_COLS;
extern int MAX_ROWS;
extern int MAX_MINES;
typedef struct {
    char** board;
    bool gameover;
    int score;
} gamestate;

typedef struct {
    int row;
    int col;
} pos;
#ifndef GAME_H
#define GAME_H

#endif //GAME_H
char** setup_state();
void setup_gamestate(gamestate* state);