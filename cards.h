//
// Created by JimmiHansen on 10-04-2025.
//

typedef enum {
    CLUBS,
    SPADES,
    DIAMONDS,
    HEARTS
} Suit;

typedef struct {   // Structure declaration
    Suit suit;       // C,D,H,S
    int value;
} Card;