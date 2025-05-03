#ifndef GAME_H
#define GAME_H

#include "stack.h"
#include "deck.h"

#define NUM_TABLEAU     7
#define NUM_FOUNDATIONS 4

typedef struct {
    Stack tableau[NUM_TABLEAU];
    Stack foundations[NUM_FOUNDATIONS];
    Card* deck[DECK_SIZE];
} Game;

void init_game(Game* game);
void draw_game(const Game* game);
int perform_move(Game* game, int from_col, int from_pos, int to_col);
int load_deck_from_file(Game* game, const char* filename);
int load_deck(Game* game, const char* filename);
void init_game(Game* game);
void draw_game(const Game* game);

#endif // GAME_H