//
// Created by JimmiHansen on 11-04-2025.
//

// game.h
#ifndef GAME_H
#define GAME_H

#include "stack.h"
#include "deck.h"


#define NUM_TABLEAU 7
#define NUM_FOUNDATIONS 4

typedef struct Game {
    Stack tableau[NUM_TABLEAU];
    Stack foundations[NUM_FOUNDATIONS]; // not used yet
    Card* deck[DECK_SIZE];
} Game;

void init_game(Game* game);
void draw_game(const Game* game);
int perform_move(Game* game, int from_col, int from_pos, int to_col);

#endif
