#include "handlers.h"

int main(void) {
    while (true) {
        system(CLEAR);
        printf("Welcome to Gamify!\n\n\n[P]Minesweeper\n[B]Cookie Clicker\nMore coming soon.\n\n$");
        char operator = get_char();
        if (operator == 'P') {
            minesweeper();
            break;
        }else if (operator == 'B') {
            clicker();
            break;
        }
    }
}
