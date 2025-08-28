#include "game.h"
#include <ctype.h>
#include "../draw.h"

char* get_random_word() {
    return WORDS[rand() % WORD_COUNT];
}

void count(hangman* state) {
    int i = 0;
    while (state->word[i] != '\0') {
        i++;
    }
    state->word_len = i;
}

void setup_revealed(hangman* state) {
    state->revealed = malloc((state->word_len + 1) * sizeof(char));
    if (state->revealed == NULL) {
        exit(506);
    }
    state->revealed[state->word_len] = '\0';
    for (int i = 0; i < state->word_len; i++) {
        state->revealed[i] = '_';
    }
}



static char get_character(void) {
    int ch;
    do {
        ch = getchar();
        if (ch == EOF) return '\0';
    } while (ch == '\n' || ch == '\r');
    return tolower(ch);
}

char get_hangman_input(void) {
    char op, confirmation;

    printf("Enter a letter!\n\n$ ");
    op = get_character();
    system(CLEAR);
    return op;
}




hangman* setup_hangman(void) {
    srand(time(NULL));
    hangman* state = malloc(sizeof(hangman));
    if (state == NULL) {
        exit(505);
    }
    state->word = get_random_word();
    count(state);
    setup_revealed(state);
    state->lives = MAX_LIVES;
    state->score = 0;
    return state;
}

bool is_in_word(hangman* state, char choice) {
    for (int i = 0; i < state->word_len; i++) {
        if (state->word[i] == choice) {
            return true;
        }
    }
    return false;
}

void reveal_letters(hangman* state, char choice) {
    for (int i = 0; i < state->word_len; i++) {
        if (state->word[i] == choice && state->revealed[i] == '_') {
            state->revealed[i] = state->word[i];
            state->score++;
        }
    }
}

void random_reveal(hangman* state) {
    int random = rand() % state->word_len;
    while (state->revealed[random] != '_') {
        random = rand() % state->word_len;
    }
    state->revealed[random] = state->word[random];
    state->score++;
}

bool won(hangman* state) {
    if (state->score != state->word_len) {
        return false;
    }
    return true;
}

void hangman_loop(void) {
    srand(time(NULL));
    hangman* state = setup_hangman();
    while (state->lives > 0) {
        display_state(state);
        char choice = get_hangman_input();
        if (is_in_word(state, choice)) {
            reveal_letters(state, choice);
        }else {
            printf("oof tough luck... now luck decides your fate.\n");
            int random = rand() % 6;
            if (random == 0) {
                printf("lucky... you get one more chance\n");
            }else if (random == 1) {
                printf("congrats! a letter reveal...\n");
                sleep(1);
                state->lives--;
                printf("but could be wrong :)");
                random_reveal(state);
            }else if (random == 2) {
                printf("-2 lives :))\n");
                state->lives-=2;
            }else if (random == 3) {
                printf("no lives lost..\n");
            }else {
                printf("try again...\n");
                state->lives--;
            }
            sleep(2);

        }
        if (won(state)) {
            system(CLEAR);
            printf("Congrats you won.... this time tho...\nword was %s", state->word);
            sleep(2);
            return;
        }
    }
    system(CLEAR);
    printf("Congrats you lost...\nword was %s\nconsider getting good maybe?", state->word);
    sleep(2);
}