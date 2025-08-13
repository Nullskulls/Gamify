#include "draw.h"
#ifndef HANDLERS_H
#define HANDLERS_H
#endif  //HANDLERS_H
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

void player(gamestate* state, char** board);
void fill(int index, pos position, char** board, gamestate* state);
