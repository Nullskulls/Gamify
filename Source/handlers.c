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
    position.row = str[0] - 'A';
    position.col = str[1] - 'A';
    return position;
}
