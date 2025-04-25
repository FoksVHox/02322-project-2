#ifndef STACK_H
#define STACK_H

#include "card.h"

typedef struct {
    Card* top;
} Stack;

void stack_init(Stack* stack);
void stack_push(Stack* stack, Card* card);
Card* stack_pop(Stack* stack);
Card* stack_peek(Stack* stack);
Card* stack_peek_at(const Stack* stack, int pos);
Card* stack_detach_group(Stack* stack, Card* bottom);
void stack_merge_group(Stack* dest, Card* group_top);
int stack_size(Stack* stack);
void stack_print(const Stack* stack);

#endif // STACK_H
