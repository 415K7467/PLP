// pile.c
#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

// Initialiser la pile
void initStack(Stack* s, int maxSize) {
    s->items = (double*)malloc(sizeof(double) * maxSize);
    s->top = -1;
    s->maxSize = maxSize;
}

// Empiler un élément
void push(Stack* s, double item) {
    if (s->top < s->maxSize - 1) {
        s->items[++(s->top)] = item;
    } else {
        fprintf(stderr, "Erreur: pile pleine\n");
    }
}

// Dépiler un élément
double pop(Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    } else {
        fprintf(stderr, "Erreur: pile vide\n");
        exit(EXIT_FAILURE);
    }
}

// Vérifier si la pile est vide
int isEmpty(Stack* s) {
    return s->top == -1;
}