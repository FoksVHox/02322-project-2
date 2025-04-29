#include <stdio.h>
#include "game.h"
#include "card.h"
#include "stack.h"

// Helpers for color checking
static int is_red(Suit s) {
    return s == HEARTS || s == DIAMONDS;
}

void init_game(Game* g) {
    create_deck(g->deck);
    shuffle_deck(g->deck);
    deal_to_tableau(g->deck, g->tableau);
    for (int i = 0; i < NUM_FOUNDATIONS; ++i) {
        stack_init(&g->foundations[i]);
    }
}

void draw_game(const Game* g) {
    // 1) Print Foundations (unchanged)
    printf("FOUNDATIONS:\n");
    printf("  ");
    for (int f = 0; f < NUM_FOUNDATIONS; ++f) {
        Card* topF = stack_peek(&g->foundations[f]);
        char buf[4] = "--";
        if (topF && topF->face_up) {
            snprintf(buf, sizeof(buf), "%s%c",
                     rank_to_str(topF->rank),
                     suit_to_char(topF->suit));
        }
        printf("F%d:%-3s", f+1, buf);
    }
    printf("\n\n");

    // 2) Headers for the tableau
    for (int i = 0; i < NUM_TABLEAU; ++i) {
        printf("T%d   ", i + 1);
    }
    printf("\n");

    // 3) Find the tallest pile
    int heights[NUM_TABLEAU], maxh = 0;
    for (int i = 0; i < NUM_TABLEAU; ++i) {
        heights[i] = stack_size(&g->tableau[i]);
        if (heights[i] > maxh) maxh = heights[i];
    }

    // 4) Print row-by-row, bottom-of-stack first
    for (int row = 0; row < maxh; ++row) {
        for (int col = 0; col < NUM_TABLEAU; ++col) {
            int h = heights[col];
            if (row < h) {
                // Map printed-row → stack-depth:
                // row=0  → bottom-of-stack (depth = h-1)
                // row=h-1 → top-of-stack (depth = 0)
                int depth = h - 1 - row;
                Card* c = stack_peek_at(&g->tableau[col], depth);
                if (c->face_up) {
                    printf("%-4s",
                       (snprintf((char[4]){},0,"%s%c",
                                 rank_to_str(c->rank),
                                 suit_to_char(c->suit)),
                        (char[4]){rank_to_str(c->rank)[0], suit_to_char(c->suit),0}));
                } else {
                    printf("%-4s", "XX");
                }
            } else {
                // no card this deep
                printf("    ");
            }
        }
        printf("\n");
    }
    printf("\n");
}


int perform_move(Game* g, int from_col, int from_pos, int to_col) {
    printf("Attempting move: from tableau %d depth %d to %d\n", from_col, from_pos, to_col);

    // Validate source column
    if (from_col < 1 || from_col > NUM_TABLEAU) {
        printf("  ! FAILED: source column %d out of range\n", from_col);
        return 0;
    }
    Stack* src = &g->tableau[from_col - 1];
    Card* bottom = stack_peek_at(src, from_pos);
    if (!bottom) {
        printf("  ! FAILED: no card at that depth (depth %d)\n", from_pos);
        return 0;
    }
    if (!bottom->face_up) {
        printf("  ! FAILED: card at depth %d is face-down\n", from_pos);
        return 0;
    }

    // Move to foundation?
    if (to_col >= 101 && to_col < 101 + NUM_FOUNDATIONS) {
        int f = to_col - 101;
        printf("  $ Target: Foundation %d\n", f+1);
        if (from_pos != 0) {
            printf("  ! FAILED: only single-card moves to foundations allowed\n");
            return 0;
        }
        Card* topF = stack_peek(&g->foundations[f]);
        Rank expected = topF ? (Rank)(topF->rank + 1) : ACE;
        if (bottom->rank != expected) {
            printf("  ! FAILED: expected rank %d, got %d\n", expected, bottom->rank);
            return 0;
        }
        if (topF && bottom->suit != topF->suit) {
            printf("  ! FAILED: suit mismatch: foundation has %c, card is %c\n",
                   suit_to_char(topF->suit), suit_to_char(bottom->suit));
            return 0;
        }
        // perform move
        Card* moved = stack_pop(src);
        stack_push(&g->foundations[f], moved);
        printf("  £ SUCCESS: moved to foundation %d\n", f+1);
        return 1;
    }

    // Move to tableau
    if (to_col < 1 || to_col > NUM_TABLEAU) {
        printf("  ! FAILED: destination column %d out of range\n", to_col);
        return 0;
    }
    printf("  $ Target: Tableau %d\n", to_col);
    Stack* dst = &g->tableau[to_col - 1];
    Card* dst_top = stack_peek(dst);

    // Empty column rules
    if (!dst_top) {
        if (bottom->rank != KING) {
            printf("  ! FAILED: only a KING can be moved to an empty column\n");
            return 0;
        }
    } else {
        // color rule
        if (is_red(bottom->suit) == is_red(dst_top->suit)) {
            printf("  ! FAILED: colors must alternate (%c over %c)\n",
                   suit_to_char(bottom->suit), suit_to_char(dst_top->suit));
            return 0;
        }
        // rank rule
        if (bottom->rank + 1 != dst_top->rank) {
            printf("  ! FAILED: rank must be one lower (%d over %d)\n",
                   bottom->rank, dst_top->rank);
            return 0;
        }
    }

    // Detach and move sequence
    Card* group_top = stack_detach_group(src, bottom);
    stack_merge_group(dst, group_top);
    // Flip next card if needed
    Card* new_top = stack_peek(src);
    if (new_top && !new_top->face_up) {
        new_top->face_up = 1;
        printf("  $ Flipped card %s%c face-up\n",
               rank_to_str(new_top->rank), suit_to_char(new_top->suit));
    }
    printf("  → SUCCESS: moved sequence to tableau %d\n", to_col);
    return 1;
}

