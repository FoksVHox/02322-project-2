#include "cards.h"
//
// Created by JimmiHansen on 10-04-2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cards.h"
#define DECK_SIZE 52

typedef struct {
    Card cards[DECK_SIZE];
    int top;
} Deck;



//load deck from file function
int load_deck(const char *file_name, Card** deck) {
    FILE * file = fopen(file_name, "r");

    //if no file is selected
    if (file == NULL) {
        printf("File not found\n");
        return -1; //return -1 so it's easier to spot errors
    }

    char line[10];
    int card_count = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;

        if (strlen(line) == 0) {
            continue;
        }

        if (strlen(line) != 2) {
            printf("Line is '%s'This string is too long or short\n", line);
            fclose(file);
            return -1;
        }

        // sorts the card order (AH, 2D, 3C, 4C, QH etc.)
        char rank = line[0];
        char suit = line[1];

        //Card* new_card = create_card(rank, suit, 0);
        //append_card(deck, new_card);
        card_count++;
    }
    fclose(file);

    //checks if deck is 52 cards (probably not necessary, but good to have just in case)
    if (card_count != 52) {
        printf("Wrong number of cards\n");
        return -1;
    }
    return 0;

}