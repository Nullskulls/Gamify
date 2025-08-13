#include <time.h>
#include "handlers.h"

int main(void) {
    int highest_score;
    if (file_exists("minesweeper_score.txt")) {
        highest_score = get_highest_score("minesweeper_score.txt"); //get the highest score from persistent storage
    }else {
        highest_score = 0; //default score to 0
        save_highest_score("minesweeper_score.txt", 0);
    }
    srand(time(NULL)); //seed random so you don't have to replay the same state over and over
    while (1) {
        printf("Welcome to Minesweeper\nPick difficulty (P: Hard, E: Medium, B: Easy)\n$");
        char level = get_char();
        if (level == 'P') {
            MAX_ROWS = 24; //make the board bigger (default is 16) and add more mines (default is 50)
            MAX_COLS = 24;
            MAX_MINES = 90;
        }else if (level == 'B') {
            MAX_ROWS = 8; //shrink the board and decrease the amount of mines
            MAX_COLS = 8;
            MAX_MINES = 12;
        }
        char** board = setup_state(); //initialize the board that is to be displayed
        gamestate* state = malloc(sizeof(gamestate)); //allocate actual memory for the game state
        if (state == NULL) {
            return 100; //exit if malloc fails
        }
        setup_gamestate(state); //set up the gamestate
        while (!state->gameover) { //while the game is not over
            system(CLEAR); //clear the screen (Linux and Windows compatible)
            draw_state(board); //each frame draw board and ask the player what they want to do
            player(state, board); //start the new input process
        }
        system(CLEAR); //if the game is over clear the screen
        draw_state(state->board); //draw the game state so the user sees what they did wrong
        count_points(state, board); //count their total points by how many flags are placed correctly and incorrectly
        if (highest_score < state->score) { //if the highscore is less than the current game score
            highest_score = state->score; //save the current game score to highscore to be used later
            save_highest_score("minesweeper_score.txt", highest_score); //save the highest score to persistent storage
        }
        printf("Game Over\nYour score is: %i!, Your highest score is: %i\n", state->score, highest_score); //display score data to user
        freer(state, board); //free all heap allocated memory
        printf("Would you like to play again? (P: Play, E: Exit)\n$"); //prompt the user for if they want to play again
        char operator = get_char();
        if (operator == 'E') { //if not exit with code error 0 (I think 0 was for everything went right)
            save_highest_score("minesweeper_score.txt", highest_score); //save the highest score to persistent storage
            exit(0);
        }
        //otherwise continue in the while loop
    }

}
