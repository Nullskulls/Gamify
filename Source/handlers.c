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
void clear_row(pos position, char** board, gamestate* state) {
    for (int j = 0; position.col + j < MAX_COLS; j++) {
        for (int i = 0; position.row + i < MAX_ROWS; i++) {
            if (state->board[position.row+i][position.col+j] == '*') {
                break;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];
        }
        for (int i = 0; position.row - i >= 0; i--) {
            if (state->board[position.row+i][position.col+j] == '*') {
                break;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];
        }
    }
    for (int j = 0; position.col + j >= 0; j--) {
        for (int i = 0; position.row + i < MAX_ROWS; i++) {
            if (state->board[position.row+i][position.col+j] == '*') {
                break;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];
        }
        for (int i = 0; position.row - i >= 0; i--) {
            if (state->board[position.row+i][position.col+j] == '*') {
                break;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];
        }
    }
}

void clean(pos position, char** board, gamestate* state) {
    clear_row(position, board, state);
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
