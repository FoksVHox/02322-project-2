#include <stdio.h>
#include <stdlib.h>
#include "card.h"

#include <ctype.h>
#include <string.h>

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

int rank_to_enum(const char* rank) {
    if (strcmp(rank, "A") == 0) return 0;
    if (strcmp(rank, "2") == 0) return 1;
    if (strcmp(rank, "3") == 0) return 2;
    if (strcmp(rank, "4") == 0) return 3;
    if (strcmp(rank, "5") == 0) return 4;
    if (strcmp(rank, "6") == 0) return 5;
    if (strcmp(rank, "7") == 0) return 6;
    if (strcmp(rank, "8") == 0) return 7;
    if (strcmp(rank, "9") == 0) return 8;
    if (strcmp(rank, "10") == 0|| strcmp(rank, "T") == 0) return 9;
    if (strcmp(rank, "J") == 0) return 10;
    if (strcmp(rank, "Q") == 0) return 11;
    if (strcmp(rank, "K") == 0) return 12;
    return -1;  // Invalid rank
}

int suit_to_enum(char suit) {
    switch (toupper(suit)) {
        case 'S': return 0;
        case 'H': return 1;
        case 'D': return 2;
        case 'C': return 3;
        default: return -1;  // Invalid suit
    }
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
