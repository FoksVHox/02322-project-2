#include <stdlib.h>
#include <time.h>
#include "deck.h"
#include "card.h"
#include "stack.h"

void create_deck(Card* deck[DECK_SIZE]) {
    int idx = 0;
    for (Suit s = HEARTS; s <= SPADES; ++s) {
        for (Rank r = ACE; r <= KING; ++r) {
            deck[idx++] = create_card(s, r);
        }
    }
}

void shuffle_deck(Card* deck[DECK_SIZE]) {
    srand((unsigned)time(NULL));
    for (int i = DECK_SIZE - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        Card* tmp = deck[i];
        deck[i] = deck[j];
        deck[j] = tmp;
    }
}



void deal_to_tableau(Card* deck[DECK_SIZE], Stack tableau[NUM_TABLEAU]) {
    int lengths[NUM_TABLEAU] = {1, 6, 7, 8, 9, 10, 11};
    int idx = 0;

    for (int i = 0; i < NUM_TABLEAU; ++i) {
        stack_init(&tableau[i]);
        int face_down_count = lengths[i] > 5 ? lengths[i] - 5 : 0;
        for (int j = 0; j < lengths[i]; ++j) {
            Card* c = deck[idx++];
            c->face_up = (j < face_down_count) ? 0 : 1;
            stack_push(&tableau[i], c);
        }
    }
}