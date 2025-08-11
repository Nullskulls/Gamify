//
// Created by Segfault on 8/11/2025.
//

#include "game.h"
int MAX_COLS = 16;
int MAX_ROWS = 16;
int MAX_MINES = 40;
void clear(gamestate* state) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            state->board[i][j] = ' ';
        }
    }
}
pos valid_coords(char** board) {
    pos position;
    position.row = 0;
    position.col = 0;
    while (board[position.row][position.col] != ' ') {
        position.row = rand() % MAX_ROWS;
        position.col = rand() % MAX_COLS;
    }
    return position;
}
void fill_board(gamestate* state) {
    for (int i = 0; i < MAX_MINES; i++) {
        pos position = valid_coords(state->board);
        state->board[position.row][position.col] = '*';

    }
}

void enumarate_board(gamestate* state) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (state->board[i][j] == ' ') {
                int number = 0;
                for (int foo = 1; foo > -2; foo--) {
                    for (int bar = 1; bar > -2; bar--) {
                        if (i+bar >= MAX_ROWS || j+foo >= MAX_COLS || i+bar < 0 || j+foo < 0) {
                            continue;
                        }
                        if (state->board[i+bar][j+foo] == '*' && foo != 0 && bar != 0) {
                            number++;
                        }
                    }
                }
                state->board[i][j] = number;
            }
        }
    }
}

void setup_gamestate(gamestate* state) {
    state->gameover = false;
    state->board = malloc(MAX_ROWS * sizeof(char*));
    if (state->board == NULL) {
        free(state);
        exit(101);
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        state->board[i] = malloc(sizeof(char)*MAX_COLS);
        if (state->board[i] == NULL) {
            for (int foo = 0; foo > i; foo++) {
                free(state->board[foo]);
            }
            exit(102);
        }
    }
    clear(state);
    fill_board(state);
    enumarate_board(state);
}

char** setup_state() {
    char** board = malloc(MAX_ROWS * sizeof(char*));
    if (board == NULL) {
        exit(103);
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        board[i] = malloc(MAX_COLS * sizeof(char));
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            board[i][j] = '?';
        }
    }
    return board;
}
