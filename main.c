#include <stdio.h>

#include "deck.h"
#include "stack.h"

int main(void) {
    Card* deck[DECK_SIZE];
    Stack tableau[NUM_TABLEAU];

    create_deck(deck);
    shuffle_deck(deck);
    deal_to_tableau(deck, tableau);

    for (int i = 0; i < NUM_TABLEAU; i++) {
        printf("Pile %d: ", i + 1);
        stack_print(&tableau[i]);
    }
}

void print_board() {

}