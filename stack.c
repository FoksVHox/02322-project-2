#include <stdio.h>
#include "stack.h"
#include "card.h"

void stack_init(Stack* s) {
    s->top = NULL;
}

void stack_push(Stack* s, Card* c) {
    c->next = s->top;
    if (s->top) s->top->prev = c;
    c->prev = NULL;
    s->top = c;
}

Card* stack_pop(Stack* s) {
    if (!s->top) return NULL;
    Card* c = s->top;
    s->top = c->next;
    if (s->top) s->top->prev = NULL;
    c->next = c->prev = NULL;
    return c;
}

Card* stack_peek(Stack* s) {
    return s->top;
}

Card* stack_peek_at(const Stack* s, int pos) {
    Card* cur = s->top;
    for (int i = 0; cur && i < pos; ++i) {
        cur = cur->next;
    }
    return cur;
}

Card* stack_detach_group(Stack* s, Card* bottom) {
    if (!bottom) return NULL;
    Card* group_top = s->top;
    Card* remainder = bottom->next;
    if (remainder) remainder->prev = NULL;
    s->top = remainder;
    bottom->next = NULL;
    return group_top;
}

void stack_merge_group(Stack* dest, Card* group_top) {
    if (!group_top) return;
    if (!dest->top) {
        dest->top = group_top;
        return;
    }
    Card* tail = group_top;
    while (tail->next) tail = tail->next;
    tail->next = dest->top;
    dest->top->prev = tail;
    dest->top = group_top;
}

int stack_size(Stack* s) {
    int n = 0;
    for (Card* c = s->top; c; c = c->next) ++n;
    return n;
}

void stack_print(const Stack* s) {
    for (Card* c = s->top; c; c = c->next) {
        if (c->face_up) {
            printf("%2s%c ", rank_to_str(c->rank), suit_to_char(c->suit));
        } else {
            printf("XX ");
        }
    }
    printf("\n");
}