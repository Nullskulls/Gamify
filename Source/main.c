#include "draw.h"

int main(void) {
    gamestate* state = malloc(sizeof(gamestate));
    if (state == NULL) {
        return 100;
    }
    setup_gamestate(state);
    draw_state(state);
}