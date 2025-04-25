#include <stdio.h>
#include <stdlib.h>
#include "card.h"

char suit_to_char(Suit suit) {
    switch (suit) {
        case HEARTS:   return 'H';
        case DIAMONDS: return 'D';
        case CLUBS:    return 'C';
        case SPADES:   return 'S';
        default:       return '?';
    }
}

const char* rank_to_str(Rank rank) {
    static const char* names[] = {
        "?", "A", "2", "3", "4", "5", "6",
        "7", "8", "9", "10", "J", "Q", "K"
    };
    if (rank < ACE || rank > KING) return names[0];
    return names[rank];
}

Card* create_card(Suit suit, Rank rank) {
    Card* card = malloc(sizeof(Card));
    if (!card) {
        fprintf(stderr, "Failed to allocate memory for card\n");
        exit(1);
    }
    card->suit = suit;
    card->rank = rank;
    card->face_up = 0;
    card->next = NULL;
    card->prev = NULL;
    return card;
}

void free_card_list(Card* card) {
    while (card) {
        Card* next = card->next;
        free(card);
        card = next;
    }
}
