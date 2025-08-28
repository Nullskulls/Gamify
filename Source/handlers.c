#include "handlers.h"

/*
 *Function to see if the user's input is invalid, It's not foolproof tho it works.
 */
bool invalid_input(const char* str) {
    if (str[2] != '\0') {//if third index of the input is not the string termination char
        return true; //return that the input is invalid
    }
    if (str[0] - 'A' >= MAX_ROWS || str[1] - 'A' >= MAX_COLS || str[0] - 'A' < 0 || str[1] - 'A' < 0) { //first and second index of the str are not between A-P
        return true; //return that the input is invalid
    }
    return false; //if all conditions are false return
}


/*
 *Function to see if the user inputted operator is within the specified 3 (or if I add more)
 */
bool invalid_operator(const char operator) {
    if (operator == 'U' || operator == 'F' || operator == 'P' || operator == 'E' || operator == 'B' || operator == '`') { //if the operator is (U, F, P, E, B, `)
        return false; //return that the operator is valid
    }
    return true; //otherwise return invalid
}


void str_to_upper(char *s) {
    char* temp = malloc(3*sizeof(char));
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] = toupper(s[i]);
    }
}

/*
 *Function used to prompt the user for cords input (checking for validity implemented)
 */
pos get_input() {
    char* str = malloc(sizeof(char)*3); //allocate 3 chars (1 terminator char and 2 input)
    if (str == NULL) {
        exit(105); //if malloc fails exit with special exit code
    }
    do {
        scanf("%2s", str);
        str_to_upper(str);
    }while (invalid_input(str)); //keep getting input until the user input is valid
    pos position;
    position.row = 'A' + MAX_ROWS - 1 - str[0];
    position.col = str[1] - 'A'; //turn the user input from chars to indexing
    free(str); //free the string allocated memory
    return position; //return the index of the user inputted tile
}


/*
 *Function to fill from bottom to top
 */
void fill_top(pos position, char** board, gamestate* state) {
    pos tmp = position; //create a copy of the cords to be passed to fill later
    for (int i = -1; i <= 1; i++) {
        if (position.col+i < 0 || position.col+i >= MAX_COLS || position.row >= MAX_ROWS || state->board[position.row][position.col + i] == '*') {
            continue; //if out of bounds (col wise) continue
        }
        if (position.row-1 < 0 || position.row > MAX_ROWS) {
            break; //if row is out of bounds break to avoid endless recursion
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i]; //set the current tile to what it is in the state
        tmp.col = position.col + i; //increment col by i
        fill(-1, tmp, board, state); //pass it to fill
    }
}
/*
 *Function from top to bottom
 */
void fill_bottom(pos position, char** board, gamestate* state) {
    pos tmp = position; //same as top pretty much so leaving undocumented
    for (int i = -1; i <= 1; i++) {
        if (position.col+i < 0 || position.col+i >= MAX_COLS || position.row >= MAX_ROWS || state->board[position.row][position.col + i] == '*') {
            continue;
        }
        if (position.row+1 < 0 || position.row+1 >= MAX_ROWS) {
            break;
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i];
        tmp.col = position.col + i;
        fill(1, tmp, board, state);
    }
}


/*
 *Main floodfill helper function
 */
void fill(int index, pos position, char** board, gamestate* state){
    if (index == -1) { //if index is -1 (going upwards due to how 2D arrays are and im not a hooligan and printing it backwards
        for (int i = -1; i <= 1; i++) {
            pos tmp = position; //make a copy of the cords to be passed to fill top later
            if (position.col + i >= MAX_COLS || position.col + i < 0) { //if col is out of bounds skip
                continue;
            }
            if ( position.row + index < 0 || position.row + index >= MAX_ROWS) {
                break; //if row is out of bounds break
            }
            tmp.row += index; //increment the row by index (go upwards)
            tmp.col += i; //increment the col by i (left, right or center depending on i)
            if (tmp.row-1 > 0 && (board[tmp.row-1][tmp.col] != '?' && board[tmp.row-1][tmp.col] != 'F')) { //if tile has been cleared before
                continue; //skip
            }
            fill_top(tmp, board, state); //pass new cords to fill top to keep doing it until you reach a trap or the top
        }
    }
    else if (index == 1) { //else if index is 1 (going downwards) <yes I know it gets confusing>
        for (int i = -1; i <= 1; i++) {
            pos tmp = position; //make a copy same as above
            if (position.col + i >= MAX_COLS || position.col + i < 0) {
                continue; //same applies for everything here so leaving undocumented
            }
            if (position.row + index < 0 || position.row + index >= MAX_ROWS) {
                break;
            }
            tmp.row += index;
            tmp.col += i;
            if (tmp.row + 1 <= MAX_ROWS-1 && (board[tmp.row+1][tmp.col] != '?' && board[tmp.row+1][tmp.col] != 'F')) {
                continue;
            }
            fill_bottom(tmp, board, state);
        }
    }
    //clearing sideways
    for (int i = -1; i <= 1; i++) {
        pos tmp = position; //make a copy of cords
        if (position.row + i >= MAX_ROWS || position.row + i < 0) {
            continue; //if
        }else if (state->board[position.row][position.col + i] == '*' || board[position.row][position.col + i] != 'F' || board[position.row][position.col + i] == '?') {
            break;
        }
        board[position.row][position.col + i] = state->board[position.row][position.col + i];
        tmp.col = position.col + i;
        fill(0, tmp, board, state);
    }
}

/*
 *Function made as a failsafe, if a number incremented is 0 it just clears everything around it
 */
void final_passthrough(char** board, gamestate* state) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (board[i][j] == 0) {
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (i + l < MAX_ROWS && i + l >= 0 && j + k < MAX_COLS && j + k >= 0) {
                            board[i + l][j + k] = state->board[i + l][j + k];
                        }
                    }
                }
            }
        }
    }
}

/*
 *Main flood filling function
 */
void floodfill(pos position, char** board, gamestate* state) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (position.row+i >= MAX_ROWS || position.col+j >= MAX_COLS || position.row+i < 0 || position.col+j < 0 || state->board[position.row+i][position.col+j] == '*') {
                continue;
            }
            board[position.row+i][position.col+j] = state->board[position.row+i][position.col+j];

        }
        fill(i, position, board, state);
    }
    final_passthrough(board, state); //run one last pass through just incase something fell through the cracks
}


/*
 *Function used to handle the user pressing on a tile
 */
void press(pos position, char** board, gamestate* state) {
    if (state->board[position.row][position.col] == '*') { //if said tile is a trap mark game state as over
        state->gameover = true;
    }
    floodfill(position, board, state); //otherwise start flood filling from said tile
}


/*
 *Function to get a single char
 */
char get_char() {
    char operator;
    do{
        scanf("%c", &operator);
        operator = toupper(operator);
    }while (invalid_operator(operator)); //while the user input is invalid keep scanning for input
    return operator;
}

/*
 *Function used to handle all user interaction with the board
 */
void player(gamestate* state, char** board) {
    pos position = get_input(); //start by getting index of the tile from user

    printf("Operations: (F: Set to flag, U: Unflag, P: Press, E: End, B: Back)\n$");
    char operator = get_char();

    if (operator == 'F') { //if user wants to add a flag set the flag down on the user viewed board
        board[position.row][position.col] = 'F';
    }else if (operator == 'U') {
        //if the user unflags a position set it back to '?'
        board[position.row][position.col] = '?';
    }else if (operator == 'E') {
        state->gameover = true; // set the game over flag to be true so the end sequence can start
    }else if (operator == 'B') {
        //do nothing lol
    }else if (operator == '`') { // cheat mode if you want to cheat lol
        printf("Cheat mode activated!\n");
        draw_state(state->board); //draw the inner game state so the user can see where the mines are
        sleep(2); //sleep for two seconds so the user has time to actually react
    }else { //otherwise (which is going to be P) send position to a handler function to handle the user's press
        press(position, board, state);
    }
}

/*
 *Function to free all heap allocated memory after each round
 */
void freer(gamestate* state, char** board) {
    for (int i = 0; i < MAX_ROWS; i++) {
        free(board[i]); // free each list inside the 2d array
        free(state->board[i]);
    }
    free(board);
    free(state);
}


/*
 *Function used to count player's total score after each round
 */
void count_points(gamestate* state, char** board) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (board[i][j] == 'F') { //if the user set down a flag
                if (state->board[i][j] == '*') { //if a trap is there
                    state->score += 10; //increase their score by 10
                }
                else {
                    state->score -= 10; //otherwise decrease their score by 10
                }
            }
        }
    }
}

int file_exists(const char* filename) {
    FILE* file; //initialize a file pointer
    if ((file = fopen(filename, "r"))) { //if fopen returns a pointer
        fclose(file); //close the file to avoid unexpected behavior
        return 1; //return true
    }
    return 0; // else return false
}

int get_highest_score(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit( 303);
    }
    char buffer[16];
    if (!fgets(buffer, sizeof(buffer), file)) {
        fprintf(stderr, "Error reading file");
        fclose(file);
        exit(304);
    }
    int value = atoi(buffer);
    fclose(file);
    return value;
}

void save_highest_score(const char* filename, int score) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "%d", score);

}
#ifdef _WIN32
void sleep(unsigned int seconds) {
    Sleep(seconds * 1000);
}
#endif

void minesweeper() {
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
            exit(100); //exit if malloc fails
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
            break;
        }
        //otherwise continue in the while loop
    }
}
/*
 *Function to validate user input during the cookie clicker promps
 */
bool invalid_cookie(char operator) {
    if (operator != 'E' && operator != 'R' && operator != 'S' && operator != 10 && operator != 13 && operator != 'H') {
        return true;
    }
    return false;
}
/*
 *Function to get and validate user input
 */
char  get_prompt_cookie() {
    char operator;
    do{
        scanf("%c", &operator);
        operator = toupper(operator);
    }while (invalid_cookie(operator)); //while the user input is invalid keep scanning for input
    return operator;
}
/*
 *Function to Set up the game state for the cookie game
 */
void setup_cookie_state(cookie* state) {
    state->rebirth = 1;
    state->bonus = false;
    state->cookies = 0;
    state->multiplier = 1;
    state->luck = 100;
}
/*
 *Function to get valid integer user input
 */
int get_int() {
    int operator;
    scanf("%i", &operator);
    if (operator > 0 && operator < 9) {
        return operator;
    }
    return get_int();
}

/*
 *Function used to display the shop products to the user and allows them to buy too.
 */
void shop(cookie* state) {
    printf(
        "Available for purchase:-\n\n[1] Extra keyboard: 100 Cookies\n *Adds a +1 Cookie multiplier\n[2] More Fingers: 500 Cookies\n *Adds a +5 Cookie multiplier\n[3] More computers: 2,000 Cookies\n *Adds +25 Cookie multiplier\n -There only so many USB ports </3\n");
    printf(
        "[4] Hire a relative to click: 50,000 Cookies\n *Adds +600 Cookie multiplier\n -Create your army!!!\n[5] Dunk them in milk: 200,000\n *Adds +1500 Cookie multiplier\n *It somehow duplicates now???\n[6] Make a cookie firm: 10,000,000\n *Adds +5000 Cookie Multiplier\n -We offer health insurance too");
    printf(
        "\n[7] Expand.. : 200,000,000 Cookies\n *Adds +75,000 Cookie multiplier\n -We are everywhere.\n[8] Cookie Dungeon: 1,000,000,000\n *Adds +250,000 Cookie multiplier\n -Gotta store em somewhere ;-;");
    if (state->rebirth > 1 && state->rebirth < 3) {
        printf("\n[9] Buy the moon: 100,000,000,000\n *Adds +12000000000 Cookie multiplier\n -Just why...\n[10] Rent the sun: 999,890,111,111,111\n *Adds +70,000,000,000,000\n -Who the hell are you getting this shit from");
    }else if (state->rebirth > 2) {
        printf("\n[11] Just edit the source code: 1 Cookie\n *Adds inf or 0 cookies can't decide :3\n -Could've saved you and me ALOT of time.\n");
    } //shop handler pretty self explantory
    printf("\n\n$");
    int operator = get_int();
    if (operator == 1) {
        if (state->cookies < 100) {
            printf("Not enough cookies brokie.\n");
            sleep(1);
            return;
        }
        state->cookies -= 100;
        state->multiplier++;
    }else if (operator == 2) {
        if (state->cookies < 500) {
            printf("This isn't a charity...\n");
            sleep(1);
            return;
        }
        state->cookies -= 500;
        state->multiplier+=5;
    }else if (operator == 3) {
        if (state->cookies < 2000) {
            printf("Your pc caught fire. \n");
            sleep(1);
            return;
        }
        state->cookies -= 2000;
        state->multiplier+=25;
    }else if (operator == 4) {
        if (state->cookies < 50000) {
            printf("You got left on seen.\n");
            sleep(1);
            return;
        }
        state->cookies -= 50000;
        state->multiplier+=600;
    }else if (operator == 5) {
        if (state->cookies < 200000) {
            printf("You spilled the milk somehow...\n");
            sleep(1);
            return;
        }
        state->cookies -= 200000;
        state->multiplier+=1500;
    }else if (operator == 6) {
        if (state->cookies < 100000000) {
            printf("Deal fell through..\n");
            sleep(1);
            return;
        }
        state->cookies -= 100000000;
        state->multiplier+=5000;
    }else if (operator == 7) {
        if (state->cookies < 200000000) {
            printf("You got sued for having a monopoly..\n");
            sleep(1);
            return;
        }
        state->cookies -= 200000000;
        state->multiplier+=75000;
    }else if (operator == 8) {
        if (state->cookies < 1000000000) {
            printf("The dungeon collapsed ontop of your treasured cookies..\n");
            sleep(1);
            return;
        }
        state->cookies -= 1000000000;
        state->multiplier+=250000;
    }else if (state->multiplier < 1) {
        printf("item doesn't exist or not unclocked");
    }else {
        printf("adding soon...");
    }
}


/*
 *Function used to display rebirth reqirements to the user and finalize their rebirth
 */
void rebirth(cookie* state) {
    if (state->rebirth < 2) { //if the user hasn't reached their first rebirth
        printf(
            "Rebirth costs 10,000,000,000 \nAre you sure you would like to rebirth?\n *Benefits include:\n  -More items unlocked\n  -2X Multiplier\n  -Nice flex\n\n[1]Yes\n[2]No\n\n$"); //prompt them for the reqs and benifits of the first rebirth
        int operator = get_int(); //get if the user confirmed
        if (operator == 1) {
            if (state->cookies < 10000000000) { //if they can't afford the rebirth tell them
                printf("Bro... come back when you have enough ;-;\n");
                sleep(1);
                return;
            }
            state->cookies -= 10000000000; //otherwise inc the rebirth counter and subtract the amount required
            state->rebirth+=1;
            state->multiplier = 1;
        }
    }else if (state->rebirth < 3) { //if they're on their second rebirth
        printf(
            "Rebirth costs 1,000,000,000,000 \nAre you sure you would like to rebirth?\n *Benefits include:\n   -More items unclocked\n  -3X Multiplier\n\n[1] Yes\n[2] No\n\n$");
        int operator = get_int();
        if (operator == 1) {
            if (state->cookies < 1000000000000) {
                printf("Why do you even try.\n");
                sleep(1);
                return;
            }
            state->cookies -= 1000000000000;
            state->rebirth+=1;
            state->multiplier=1;
        }
    }else { //didn't add this yet
        printf("How much patience do you have??????\n");
        sleep(5);
        return;
    }
}
/*
 *Function that handles the main game logic loop
 */
void clicker(void) {
    srand(time(NULL)); //seed random so its more playable
    cookie* state = malloc(sizeof(cookie)); //allocate memory for the cookie game state
    setup_cookie_state(state);
    while (true) {
        system(CLEAR);
        cookie_prompt(state); //show the user their HUD (multiplier options count etc)
        char operator = get_prompt_cookie();
        if (operator == 13 || operator == 10) { //if user pressed enter
            if (rand() % state->luck == 1) { //1 in 100 chance they get a 2x multi that time
                state->cookies += 2*state->multiplier*state->rebirth;
                state->bonus = true; //set the bonus flag to true so it's displayed from the HUD
            }else {
                state->cookies += state->multiplier*state->rebirth; //otherwise don't double
            }
        }else if (operator == 'H') {
            system(CLEAR);
            printf("How to play:\n\n->Press enter to get cookies\n->You by default have a 1 in 100 got getting a crit\n *A crit gives 2X your multiplier\nYou can increase your multiplier by pressing S to open the shop\n\n$");// print instructions on how to play
            sleep(7); //sleep so the user gets to see what was written
        }else if (operator == 'E') { //if user chooses to exit
            free(state); //clean up heap allocated memory
            break; //exit the game loop to the outer game loop
        }else if (operator == 'S') { //open shop
            system(CLEAR);
            shop(state);
        }else if (operator == 'R') { //rebirth
            rebirth(state);
        }
    }
}