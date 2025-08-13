#include "handlers.h"
#include "hangman/game.h"
int main(void) {
    while (true) {
        system(CLEAR);
        test();
        printf("Welcome to Gamify!\n\n\n[P]Minesweeper\n[B]Cookie Clicker\n[E]Hang Man\nMore coming soon.\n\n$");
        char operator = get_char();
        if (operator == 'P') {
            minesweeper();
        }else if (operator == 'B') {
            clicker();
        }else if (operator == 'E') {

        }
        system(CLEAR);
        printf("Would you like to exit or switch games?\n[P] Exit\n [B] Continue\n\n$");
        operator = get_char();
        if (operator == 'P') {
            exit(0);
        }
    }
}
