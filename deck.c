#include "cards.h"
//
// Created by JimmiHansen on 10-04-2025.
//
#define DECK_SIZE 52

typedef struct {
    Card cards[DECK_SIZE];
    int top;
} Deck;