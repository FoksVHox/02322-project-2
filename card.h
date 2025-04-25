//
// Created by JimmiHansen on 10-04-2025.
//

typedef enum {
    HEARTS, DIAMONDS, CLUBS, SPADES
} Suit;

typedef enum {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
    EIGHT, NINE, TEN, JACK, QUEEN, KING
} Rank;

typedef struct Card {
    Suit suit;
    Rank rank;
    int face_up;              // 1 = face up, 0 = face down
    struct Card* next;        // next card in stack (below)
    struct Card* prev;        // previous card (above, for moving sequences)
} Card;

char suit_to_char(Suit suit);
const char* rank_to_str(Rank rank);
Card* create_card(Suit suit, Rank rank);
void free_card_list(Card* card);
