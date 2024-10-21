// pile.h
#ifndef PILE_H
#define PILE_H

typedef struct {
    double* items;
    int top;
    int maxSize;
} Stack;

// Function declarations
void initStack(Stack* s, int maxSize);
void push(Stack* s, double item);
double pop(Stack* s);
int isEmpty(Stack* s);

#endif // PILE_H