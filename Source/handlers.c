#include "handlers.h"

bool invalid_input(const char* str) {
    if (str[2] != '\0') {
        return true;
    }
    if (str[0] - 'A' >= MAX_ROWS || str[1] - 'A' >= MAX_COLS || str[0] - 'A' < 0 || str[1] - 'A' < 0) {
        return true;
    }
    return false;
}

bool invalid_operator(const char operator) {
    if (operator == 'U' || operator == 'F' || operator == 'P') {
        return false;
    }
    return true;
}

pos get_input() {
    char* str = malloc(sizeof(char)*3);
    if (str == NULL) {
        exit(105);
    }
    str[0] = 'Q';
    str[1] = 'Q';
    str[2] = '\0';
    while (invalid_input(str)) {
        scanf("%2s", str);
    }
    pos position;
    position.row = 'P' - str[0];
    position.col = str[1] - 'A';
    free(str);
    return position;
}


void clean(pos position, char** board, gamestate* state) {
    pos temp = position;
    board[position.row][position.col] = state->board[position.row][position.col];
    for (int foo = -1; foo <= 1; foo++) {
        for (int bar = -1; bar <= 1; bar++) {
            if (position.row + foo >= MAX_ROWS || position.col + bar >= MAX_COLS || position.row + foo < 0 || position.col + bar < 0) {
                continue;
            }
            if (state->board[position.row + foo][position.col + bar] != '*' && board[position.row + foo][position.col + bar] == '?') {
                temp.row = position.row + foo;
                temp.col = position.col + bar;
                clean(temp, board, state);
            }
            else {
                return;
            }
        }
    }
}

void press(pos position, char** board, gamestate* state) {
    if (state->board[position.row][position.row] == '*') {
        printf("you lost!");
        draw_state(state->board);
        exit(0);
    }
    clean(position, board, state);
}

void player(gamestate* state, char** board) {
    pos position = get_input();
    char operator = 'q';
    printf("Operations: (F: Set to flag, U: Unflag, P: Press)");
    while (invalid_operator(operator)) {
        scanf("%c", &operator);
    }
    if (operator == 'F') {
        board[position.row][position.col] = 'F';
    }else if (operator == 'U') {
        board[position.row][position.col] = '?';
    }else {
        press(position, board, state);
    }
}
