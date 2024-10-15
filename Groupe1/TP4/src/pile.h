#ifndef PILE_H
#define PILE_H

#define MAX_SIZE 100

typedef struct {
    char items[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* s);
int isFull(Stack* s);
int isEmpty(Stack* s);
void push(Stack* s, char item);
char pop(Stack* s);
char peek(Stack* s);
int priority(char operator);

#endif // PILE_H
