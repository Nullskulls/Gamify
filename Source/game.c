//
// Created by Segfault on 8/11/2025.
//

#include "game.h"
int MAX_COLS = 16;
int MAX_ROWS = 16;
int MAX_MINES = 40;

/*
 *Function to clear the allocated board memory in the game state
 */
void clear(gamestate* state) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            state->board[i][j] = ' '; // for col in row item is equal to the char ' ' which is symbol for uninitialized in this code base
        }
    }
}

/*
 *Function to get a valid set of cords when placing something
 */
pos valid_coords(char** board) {
    pos position;
    position.row = 0;
    position.col = 0; //initialize the base row and col for the radom cords
    while (board[position.row][position.col] != ' ') { //if the cords have something inside them try again
        position.row = rand() % MAX_ROWS; //get a number from [0-16[
        position.col = rand() % MAX_COLS;
    }
    return position;
}

/*
 *Function used to add all the traps on the board
 */
void fill_board(gamestate* state) {
    for (int i = 0; i < MAX_MINES; i++) {
        pos position = valid_coords(state->board); //get  random valid cords using a helper function
        state->board[position.row][position.col] = '*'; //place the trap at said cords

    }
}


/*
 *Function used to see how many traps each empty tile is touching and place it in the game state
 */
void enumarate_board(gamestate* state) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (state->board[i][j] == ' ') { //if cords are empty
                int number = 0; //initialize number of traps it's touching to zero
                for (int foo = 1; foo > -2; foo--) {
                    for (int bar = 1; bar > -2; bar--) { //for every tile the tile is touching self included
                        if (i+bar >= MAX_ROWS || j+foo >= MAX_COLS || i+bar < 0 || j+foo < 0) {
                            continue; //if out of index pass
                        }
                        if (state->board[i+bar][j+foo] == '*'){
                            number++; //if the tile that it's touching is a trap increase the before initialized number variable by one
                        }
                    }
                }
                state->board[i][j] = number; //set the tile in the game state (which is not viewed by the user) to the number that the tile is touching
            }
        }
    }
}


/*
 *Function used to initialize the game state the first time the game is run
 */
void setup_gamestate(gamestate* state) {
    state->score = 0;
    state->gameover = false;
    state->board = malloc(MAX_ROWS * sizeof(char*)); //allocate memory for the state's board
    if (state->board == NULL) {
        free(state); //if malloc fails, free and exit with code 101
        exit(101);
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        state->board[i] = malloc(sizeof(char)*MAX_COLS);
        if (state->board[i] == NULL) {
            for (int foo = 0; foo > i; foo++) {
                free(state->board[foo]);
            }
            free(state->board);
            free(state); //if malloc fails free all allocated memory
            exit(102);
        }
    }
    clear(state); //fill the board with ' ' to get rid of unwanted garbage values
    fill_board(state); //fill the board with traps
    enumarate_board(state); //enumerate how many each tile is touching
}


/*
 *Function used to set up and allocare memory for the user viewed board
 */
char** setup_state() {
    char** board = malloc(MAX_ROWS * sizeof(char*));
    if (board == NULL) {
        exit(103); //if malloc fails exit with code 103 (I tried making each malloc error code diff, so I can better diagnose)
    }
    for (int i = 0; i < MAX_ROWS; i++) {
        board[i] = malloc(MAX_COLS * sizeof(char));
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            board[i][j] = '?'; //set every single tile to ? to symbolify unopened/unseen by the user
        }
    }
    return board;
}
