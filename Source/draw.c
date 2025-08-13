#include "draw.h"
/*
 *Function used to display the board and game state when needed with indexing
 */
void draw_state(char** state) {
    printf("  "); //start by making space away from the left side
    for (int i = 0; i < MAX_COLS*2+2; i++) {
        printf("#"); //create the top border
    }
    printf("\n"); //start new line
    for (int i = 0; i < MAX_ROWS; i++) {
        printf("%c #", (MAX_ROWS-1+'A')-i); //draw index  P-A
        for (int j = 0; j < MAX_COLS; j++) {
            if (state[i][j] == 'F' || state[i][j] == '?' || state[i][j] == '*') { //if the tile has any of these chars print it as a char
                printf("%c ", state[i][j]);
            }else { //otherwise display as int
                printf("%i ", state[i][j]);
            }
        }
        printf("#\n"); //start new line
    } //repeat
    printf("  "); //make space away from the left side of the terminal
    for (int i = 0; i < MAX_COLS*2+2; i++) {
        printf("#"); //create bottom border
    }
    printf("\n   "); //start new line and make space for bottom indexing
    for (int i = 0; i < MAX_ROWS; i++) {
        printf("%c ", 'A'+ i); //draw A-P
    }
    printf("\nEnter position! (example: AA <ROW-COL)\n$"); //display input instructions
}

void cookie_prompt(cookie* state) {
    printf("COOOOKIESSS\n\n\nCookie count: %i    Cookie multiplier: %i     You have a 1 in %i chance for a crit.\n(Press enter to gather cookies, E to Exit, S to open the shop, R to rebirth, H for help menu)\n\n$", state->cookies, state->multiplier, state->luck);
    if (state->bonus == true) {
        state->bonus = false;
        printf("BONUS!");
    }
}