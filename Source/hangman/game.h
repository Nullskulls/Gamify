#ifndef GAME_H
#define GAME_H
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    int word_len;
    char* word;
    char* revealed;
}hangman;
void test(void);
const static char* WORDS[] = {"meow", "hackclub", "dino", "cheese", "segment", "null", "bored", "anything", "for", "blackmarket", "access", "linux", "random", "memory", "cat"};
int WORD_COUNT = 15;
#endif //GAME_H
