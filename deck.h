//
// Created by JimmiHansen on 24-04-2025.
//

#ifndef DECK_H
#define DECK_H

#include "stack.h"

#define DECK_SIZE 52
#define NUM_TABLEAU 7

void create_deck(Card* deck[DECK_SIZE]);
void shuffle_deck(Card* deck[DECK_SIZE]);
void deal_to_tableau(Card* deck[DECK_SIZE], Stack tableau[NUM_TABLEAU]);

#endif //DECK_H
