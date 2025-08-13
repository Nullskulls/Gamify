#include "draw.h"
#ifndef HANDLERS_H
#define HANDLERS_H
#endif  //HANDLERS_H
#ifdef _WIN32
#include <windows.h>
void sleep(unsigned int seconds) {
    Sleep(seconds*1000);
}
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif

void player(gamestate* state, char** board);
void fill(int index, pos position, char** board, gamestate* state);
void freer(gamestate* state, char** board);
char get_char();
void count_points(gamestate* state, char** board);