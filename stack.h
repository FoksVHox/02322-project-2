//
// Created by JimmiHansen on 11-04-2025.
//
#include "card.h"

typedef struct Stack {
    Card* top;
} Stack;


void stack_init(Stack* stack);
void stack_push(Stack* stack, Card* card);
Card* stack_pop(Stack* stack);
Card* stack_peek(Stack* stack);
int stack_size(Stack* stack);
void stack_print(Stack* stack);