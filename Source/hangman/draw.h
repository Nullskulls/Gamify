#ifndef DRAW_H
#define DRAW_H
#ifdef _WIN32
#include <windows.h>
void sleep(unsigned int seconds);
#define CLEAR "cls"
#else
#include <unistd.h>
#define CLEAR "clear"
#endif
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

extern int MAX_LIVES;
extern int WORD_COUNT;

typedef struct {
    int word_len;
    char* word;
    char* revealed;
    int lives;
    int score;
}hangman;
void display_state(const hangman* state);
#endif //DRAW_H
