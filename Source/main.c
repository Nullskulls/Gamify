#include "handlers.h"

int main(void) {
    char** board = setup_state();
    gamestate* state = malloc(sizeof(gamestate));
    if (state == NULL) {
        return 100;
    }
    get_input();
    setup_gamestate(state);
    draw_state(board);
}