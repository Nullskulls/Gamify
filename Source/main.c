#include <time.h>

#include "handlers.h"

int main(void) {
    srand(time(NULL));
    char** board = setup_state(); //initizalize the board that is to be displayed
    gamestate* state = malloc(sizeof(gamestate)); //allocate actual memory for the game state
    if (state == NULL) {
        return 100; //exit if malloc fails
    }
    setup_gamestate(state); //set up the gamestate
    while (!state->gameover) {
        system(CLEAR);
        draw_state(board); //each frame draw board and ask the player what they want to do
        player(state, board);
    }
    system(CLEAR);
    draw_state(state->board);
    printf("Game Over\n");
}
