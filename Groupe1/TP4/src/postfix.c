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

double evaluatePostfix(const char* expression) {
    Pile pile;
    initPile(&pile);

    const char* p = expression;
    char buffer[20];

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue; // Ignorer les espaces
        }

        if (isdigit(*p) || (*p == '.')) {
            // Lire un nombre
            char* end;
            double value = strtod(p, &end);
            push(&pile, value);
            p = end; // Avancer le pointeur
        } else if (strchr("+-*/", *p)) {
            double operand2 = pop(&pile);
            double operand1 = pop(&pile);
            double result;

            switch (*p) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        fprintf(stderr, "Erreur: division par zéro\n");
                        exit(EXIT_FAILURE);
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    fprintf(stderr, "Erreur: opérateur inconnu\n");
                    exit(EXIT_FAILURE);
            }
            push(&pile, result);
        }
        p++;
    }

    return pop(&pile); // La valeur finale est le résultat
}