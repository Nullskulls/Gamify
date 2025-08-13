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


/*
 *Function to fill from bottom to top
 */
void fill_top(pos position, char** board, gamestate* state) {
    pos tmp = position; //create a copy of the cords to be passed to fill later
    for (int i = -1; i <= 1; i++) {
        if (position.col+i < 0 || position.col+i >= MAX_COLS || position.row >= MAX_ROWS || state->board[position.row][position.col + i] == '*') {
            continue; //if out of bounds (col wise) continue
        }
        if (position.row-1 < 0 || position.row > MAX_ROWS) {
            break; //if row is out of bounds break to avoid endless recursion
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i]; //set the current tile to what it is in the state
        tmp.col = position.col + i; //increment col by i
        fill(-1, tmp, board, state); //pass it to fill
    }
}
/*
 *Function from top to bottom
 */
void fill_bottom(pos position, char** board, gamestate* state) {
    pos tmp = position; //same as top pretty much so leaving undocumented
    for (int i = -1; i <= 1; i++) {
        if (position.col+i < 0 || position.col+i >= MAX_COLS || position.row >= MAX_ROWS || state->board[position.row][position.col + i] == '*') {
            continue;
        }
        if (position.row+1 < 0 || position.row+1 >= MAX_ROWS) {
            break;
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i];
        tmp.col = position.col + i;
        fill(1, tmp, board, state);
    }
}


/*
 *Main floodfill helper function
 */
void fill(int index, pos position, char** board, gamestate* state){
    if (index == -1) { //if index is -1 (going upwards due to how 2D arrays are and im not a hooligan and printing it backwards
        for (int i = -1; i <= 1; i++) {
            pos tmp = position; //make a copy of the cords to be passed to fill top later
            if (position.col + i >= MAX_COLS || position.col + i < 0) { //if col is out of bounds skip
                continue;
            }
            if ( position.row + index < 0 || position.row + index >= MAX_ROWS) {
                break; //if row is out of bounds break
            }
            tmp.row += index; //increment the row by index (go upwards)
            tmp.col += i; //increment the col by i (left, right or center depending on i)
            if (tmp.row-1 > 0 && (board[tmp.row-1][tmp.col] != '?' && board[tmp.row-1][tmp.col] != 'F')) { //if tile has been cleared before
                continue; //skip
            }
            fill_top(tmp, board, state); //pass new cords to fill top to keep doing it until you reach a trap or the top
        }
    }
    else if (index == 1) { //else if index is 1 (going downwards) <yes I know it gets confusing>
        for (int i = -1; i <= 1; i++) {
            pos tmp = position; //make a copy same as above
            if (position.col + i >= MAX_COLS || position.col + i < 0) {
                continue; //same applies for everything here so leaving undocumented
            }
            if (position.row + index < 0 || position.row + index >= MAX_ROWS) {
                break;
            }
            tmp.row += index;
            tmp.col += i;
            if (tmp.row + 1 <= MAX_ROWS-1 && (board[tmp.row+1][tmp.col] != '?' && board[tmp.row+1][tmp.col] != 'F')) {
                continue;
            }
            fill_bottom(tmp, board, state);
        }
    }
    //clearing sideways
    for (int i = -1; i <= 1; i++) {
        pos tmp = position; //make a copy of cords
        if (position.row + i >= MAX_ROWS || position.row + i < 0) {
            continue; //if
        }else if (state->board[position.row][position.col + i] == '*' || board[position.row][position.col + i] != 'F' || board[position.row][position.col + i] == '?') {
            break;
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i];
        tmp.col = position.col + i;
        fill(0, tmp, board, state);
    }
}

/*
 *Function made as a failsafe, if a number incremented is 0 it just clears everything around it
 */
void final_passthrough(char** board, gamestate* state) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (board[i][j] == 0) {
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (i + l < MAX_ROWS && i + l >= 0 && j + k < MAX_COLS && j + k >= 0) {
                            board[i + l][j + k] = state->board[i + l][j + k];
                        }
                    }
                }
            }
        }
    }
}

/*
 *Main flood filling function
 */
void floodfill(pos position, char** board, gamestate* state) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (position.row+i >= MAX_ROWS || position.col+j >= MAX_COLS || position.row+i < 0 || position.col+j < 0 || state->board[position.row+i][position.col+j] == '*') {
                continue;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];

        }
        fill(i, position, board, state);
    }
    final_passthrough(board, state);
}


/*
 *Function used to handle the user pressing on a tile
 */
void press(pos position, char** board, gamestate* state) {
    if (state->board[position.row][position.col] == '*') { //if said tile is a trap exit
        state->gameover = true;
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

    printf("Operations: (F: Set to flag, U: Unflag, P: Press, E: End)\n$");

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
