//
// Created by JimmiHansen on 24-04-2025.
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void stack_init(Stack* stack) {
    stack->top = NULL;
}

void stack_push(Stack* stack, Card* card) {
    if (!card) return;

    // Find the bottom of the sequence
    Card* bottom = card;
    while (bottom->next) {
        bottom = bottom->next;
    }

    // Attach to current top
    if (stack->top) {
        stack->top->prev = bottom;
    }
    bottom->next = stack->top;

    card->prev = NULL;
    stack->top = card;
}

Card* stack_pop(Stack* stack) {
    if (!stack->top) return NULL;

    Card* top_card = stack->top;
    stack->top = top_card->next;

    if (stack->top) {
        stack->top->prev = NULL;
    }

    top_card->next = NULL;
    top_card->prev = NULL;

    return top_card;
}

Card* stack_peek(Stack* stack) {
    return stack->top;
}

int stack_size(Stack* stack) {
    int count = 0;
    Card* current = stack->top;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

void stack_print(Stack* stack) {
    Card* current = stack->top;
    while (current) {
        if (current->face_up) {
            printf("[%s%c] ", rank_to_str(current->rank), suit_to_char(current->suit));
        } else {
            printf("[??] ");
        }
        current = current->next;
    }
    printf("\n");
}