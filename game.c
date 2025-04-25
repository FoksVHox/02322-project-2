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
}x

void draw_game(const Game* g) {
    // 1) Print Foundations
    printf("FOUNDATIONS:\n");
    printf("  ");  // indent a little
    for (int f = 0; f < NUM_FOUNDATIONS; ++f) {
        Card* top = stack_peek(&g->foundations[f]);
        char buf[4] = "--";
        if (top && top->face_up) {
            snprintf(buf, sizeof(buf), "%s%c",
                     rank_to_str(top->rank),
                     suit_to_char(top->suit));
        }
        // width=4 so it lines up easily
        printf("F%d:%-3s", f+1, buf);
    }
    printf("\n\n");

    // 2) Print Tableau headers
    for (int i = 0; i < NUM_TABLEAU; ++i) {
        printf("T%d   ", i + 1);
    }
    printf("\n");

    // 3) Determine max pile height
    int heights[NUM_TABLEAU];
    int maxh = 0;
    for (int i = 0; i < NUM_TABLEAU; ++i) {
        heights[i] = stack_size(&g->tableau[i]);
        if (heights[i] > maxh) maxh = heights[i];
    }

    // 4) Print each “row” of cards across all 7 piles
    for (int row = 0; row < maxh; ++row) {
        for (int col = 0; col < NUM_TABLEAU; ++col) {
            Card* c = stack_peek_at(&g->tableau[col], row);
            char buf[4] = "";
            if (c) {
                if (c->face_up) {
                    snprintf(buf, sizeof(buf), "%s%c",
                             rank_to_str(c->rank),
                             suit_to_char(c->suit));
                } else {
                    snprintf(buf, sizeof(buf), "XX");
                }
            }
            printf("%-6s", buf);
        }
        printf("\n");
    }
    printf("\n");
}

int perform_move(Game* g, int from_col, int from_pos, int to_col) {
    if (from_col < 1 || from_col > NUM_TABLEAU) return 0;
    Stack* src = &g->tableau[from_col - 1];
    Card* bottom = stack_peek_at(src, from_pos);
    if (!bottom || !bottom->face_up) return 0;

    // Move to foundation?
    if (to_col >= 101 && to_col < 101 + NUM_FOUNDATIONS) {
        int f = to_col - 101;
        if (from_pos != 0) return 0;  // only single-card
        Card* topF = stack_peek(&g->foundations[f]);
        Rank nextRank = topF ? (Rank)(topF->rank + 1) : ACE;
        if (bottom->rank != nextRank) return 0;
        if (topF && bottom->suit != topF->suit) return 0;
        Card* moved = stack_pop(src);
        stack_push(&g->foundations[f], moved);
        return 1;
    }

    // Move to tableau?
    if (to_col < 1 || to_col > NUM_TABLEAU) return 0;
    Stack* dst = &g->tableau[to_col - 1];
    Card* dst_top = stack_peek(dst);

    // empty column: only King
    if (!dst_top) {
        if (bottom->rank != KING) return 0;
    } else {
        if (is_red(bottom->suit) == is_red(dst_top->suit)) return 0;
        if (bottom->rank + 1 != dst_top->rank) return 0;
    }

    Card* group_top = stack_detach_group(src, bottom);
    stack_merge_group(dst, group_top);

    // flip the new top if needed
    Card* new_top = stack_peek(src);
    if (new_top && !new_top->face_up) new_top->face_up = 1;

    return 1;
}
