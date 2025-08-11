#include "draw.h"

void draw_state(char** state) {
    printf("  ");
    for (int i = 0; i < MAX_COLS*2+2; i++) {
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        printf("%c #", 'P'-i);
        for (int j = 0; j < MAX_COLS; j++) {
            if (state[i][j] == '*'){
                printf("%c ", state[i][j]);
            }
            else {
                printf("%i ", state[i][j]);
            }
        }
        printf("#\n");
    }
    printf("  ");
    for (int i = 0; i < MAX_COLS*2+2; i++) {
        printf("#");
    }
    printf("\n   ");
    for (int i = 0; i < MAX_ROWS; i++) {
        printf("%c ", 'A'+ i);
    }
    printf("\nEnter position! (example: AA)");
}