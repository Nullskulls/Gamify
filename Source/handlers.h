#include <stdlib.h>
#include <stdio.h>
#include "draw.h"
#ifndef HANDLERS_H
#define HANDLERS_H
void player(gamestate* state, char** board);
void fill_next(int index, pos position, char** board, gamestate* state);
#endif //HANDLERS_H
