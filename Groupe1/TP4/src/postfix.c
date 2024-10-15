#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "postfix.h"
#include "pile.h"

char* infixToPostfix(const char* expression) {
    Stack operatorStack;
    initStack(&operatorStack);

    char* output = malloc(sizeof(char) * (strlen(expression) + 1));
    int outputIndex = 0;
    int length = strlen(expression);

    // Convertir l'expression infixée en postfixée. Pour celà on parcours l'expression
    for (int i = 0; i < length; i++) {
        if (isspace(expression[i])) {
            continue; // Ignorer les espaces
        }

        if (isdigit(expression[i])) {
            // Ajouter l'opérande à la sortie
            while (i < length && (isdigit(expression[i]) || expression[i] == '.')) {
                output[outputIndex++] = expression[i++];
            }
            output[outputIndex++] = ' '; // Espace pour séparer les opérandes
            i--; // Ajuster l'index
        } else if (expression[i] == '(') {
            // Push '(' to stack
            push(&operatorStack, expression[i]);
        } else if (expression[i] == ')') {
            // Pop tous les opérateurs jusqu'à '('
            while (!isEmpty(&operatorStack) && peek(&operatorStack) != '(') {
                output[outputIndex++] = pop(&operatorStack);
                output[outputIndex++] = ' ';
            }
            pop(&operatorStack); // Enlever '(' de la pile
        } else if (strchr("+-*/", expression[i])) { // Cas d'un opérateur (avec la gestion de la pile)
            while (!isEmpty(&operatorStack) && priority(peek(&operatorStack)) >= priority(expression[i])) {
                output[outputIndex++] = pop(&operatorStack);
                output[outputIndex++] = ' ';
            }
            push(&operatorStack, expression[i]);
        }
    }

    // Pop tout ce qui reste dans la pile
    while (!isEmpty(&operatorStack)) {
        output[outputIndex++] = pop(&operatorStack);
        output[outputIndex++] = ' ';
    }

    output[outputIndex - 1] = '\0'; // Remplacer le dernier espace par un terminateur
    return output;
}