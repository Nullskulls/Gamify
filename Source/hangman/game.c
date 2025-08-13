#include "game.h"

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

hangman* setup_hangman(void) {
    srand(time(NULL));
    hangman* state = malloc(sizeof(hangman));
    if (state == NULL) {
        exit(505);
    }
    state->word = get_random_word();
    count(state);
    return state;
}