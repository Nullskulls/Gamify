#include "handlers.h"

int main(void) {
    char** board = setup_state();
    gamestate* state = malloc(sizeof(gamestate));
    if (state == NULL) {
        return 100;
    }
    setup_gamestate(state);
    while (true) {
        draw_state(board);
        player(state, board);
    }
}
