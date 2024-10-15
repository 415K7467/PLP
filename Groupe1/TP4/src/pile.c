#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

// Cette fonction initialise une pile en réglant le curseur à -1, cela indique que la pile est vide.
void initStack(Stack* s) {
    s->top = -1;
}

// Cette fonction vérifie si la pile est pleine. Si le curseur est égal à MAX_SIZE - 1, cela signifie que la pile a atteint sa capacité maximale.
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}

// Cette fonction vérifie si la pile est vide en vérifiant si le curseur est égal à -1.
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Cette fonction ajoute un élément au sommet de la pile. Elle vérifie d'abord si la pile n'est pas pleine, puis incrémente le curseur et place l'item à cette nouvelle position.
void push(Stack* s, char item) {
    if (!isFull(s)) {
        s->items[++(s->top)] = item;
    }
}

// Cette fonction retire et retourne l'élément au sommet de la pile. Elle vérifie si la pile n'est pas vide, puis décrémente le curseur et retourne l'élément précédemment au sommet. Si la pile est vide, elle retourne le caractère null.
char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[(s->top)--];
    }
    return '\0';
}

// Cette fonction retourne l'élément au sommet de la pile sans le retirer. Si la pile est vide, elle retourne le caractère null.
char peek(Stack* s) {
    if (!isEmpty(s)) {
        return s->items[s->top];
    }
    return '\0';
}

// Cette fonction retourne la priorité des opérateurs arithmétiques. + et - ont une priorité de 1, tandis que * et / ont une priorité de 2. Les autres caractères ont une priorité de 0 par défaut.
int priority(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}
