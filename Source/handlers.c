#include "handlers.h"

/*
 *Function to see if the user's input is invalid, It's not foolproof tho it works.
 */
bool invalid_input(const char* str) {
    if (str[2] != '\0') {//if third index of the input is not the string termination char
        return true; //return that the input is invalid
    }
    if (str[0] - 'A' >= MAX_ROWS || str[1] - 'A' >= MAX_COLS || str[0] - 'A' < 0 || str[1] - 'A' < 0) { //first and second index of the str are not between A-P
        return true; //return that the input is invalid
    }
    return false; //if all conditions are false return
}


/*
 *Function to see if the user inputted operator is within the specified 3 (or if I add more)
 */
bool invalid_operator(const char operator) {
    if (operator == 'U' || operator == 'F' || operator == 'P') { //if the operator is (U, F, P)
        return false; //return that the operator is valid
    }
    return true; //otherwise return invalid
}


/*
 *Function used to prompt the user for cords input (checking for validity implemented)
 */
pos get_input() {
    char* str = malloc(sizeof(char)*3); //allocate 3 chars (1 terminator char and 2 input)
    if (str == NULL) {
        exit(105); //if malloc fails exit with special exit code
    }
    do {
        scanf("%2s", str);
    }while (invalid_input(str)); //keep getting input until the user input is valid
    pos position;
    position.row = 'P' - str[0];
    position.col = str[1] - 'A'; //turn the user input from chars to indexing
    free(str); //free the string allocated memory
    return position; //return the index of the user inputted tile
}

void fill_top(pos position, char** board, gamestate* state) {
    pos tmp = position;
    for (int i = -1; i <= 1; i++) {
        if (position.col+i < 0 || position.col+i > MAX_COLS || position.col+i > MAX_COLS || position.row > MAX_ROWS || state->board[position.row][position.col + i] == '*') {
            continue;
        }
        if (position.row-1 < 0 || position.row > MAX_ROWS) {
            break;
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i];
        tmp.col = position.col + i;
        fill_next(-1, tmp, board, state);
    }
}

void fill_next(int index, pos position, char** board, gamestate* state){
    if (index == -1) {
        for (int i = -1; i <= 1; i++) {
            pos tmp = position;
            if (position.col + i >= MAX_COLS || position.col + i < 0) {
                continue;
            }
            if ( position.row + index < 0 || position.row + index >= MAX_ROWS) {
                break;
            }
            tmp.row += index;
            tmp.col += i;
            if (tmp.row-1 > 0 && (board[tmp.row-1][tmp.col] != '?' && board[tmp.row][tmp.col] != 'F')) {
                continue;
            }
            fill_top(tmp, board, state);
        }
    }
}

void floodfill(pos position, char** board, gamestate* state) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (position.row+i >= MAX_ROWS || position.col+j >= MAX_COLS || position.row+i < 0 || position.col+j < 0 || state->board[position.row+i][position.col+j] == '*') {
                continue;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];
        }
        fill_next(i, position, board, state);
    }
}


/*
 *Function used to handle the user pressing on a tile
 */
void press(pos position, char** board, gamestate* state) {
    if (state->board[position.row][position.row] == '*') { //if said tile is a trap exit
        printf("you lost!");
        draw_state(state->board);
        exit(0);
    }
    pos* grid = malloc(sizeof(pos)*256); //test code
    if (grid == NULL) {
        exit(107);
    }
    floodfill(position, board, state);
}


/*
 *Function used to handle all user interaction with the board
 */
void player(gamestate* state, char** board) {
    pos position = get_input(); //start by getting index of the tile from user
    char operator;

    printf("Operations: (F: Set to flag, U: Unflag, P: Press)");

    do{
        scanf("%c", &operator);
    }while (invalid_operator(operator));

    if (operator == 'F') { //if user wants to add a flag set the flag down on the user viewed board
        board[position.row][position.col] = 'F';
    }else if (operator == 'U') { //if the user unflags a position set it back to '?'
        board[position.row][position.col] = '?';
    }else { //otherwise (which is going to be P) send position to a handler function to handle the user's press
        press(position, board, state);
    }
}
