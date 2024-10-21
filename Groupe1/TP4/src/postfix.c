// postfix.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "postfix.h"
#include "pile.h"


// Fonction pour ajouter un opérande à la sortie
void addOperandToOutput(const char* expression, int* i, char* output, int* outputIndex) {
    while (isdigit(expression[*i]) || expression[*i] == '.') {
        output[(*outputIndex)++] = expression[(*i)++];
    }
    output[(*outputIndex)++] = ' ';
    (*i)--;
}

// Fonction pour gérer une parenthèse fermante
void handleClosingParenthesis(Stack* operatorStack, char* output, int* outputIndex) {
    while (!isEmpty(operatorStack) && (char)operatorStack->items[operatorStack->top] != '(') {
        output[(*outputIndex)++] = (char)pop(operatorStack);
        output[(*outputIndex)++] = ' ';
    }
    pop(operatorStack); // Retirer la parenthèse ouvrante
}

// Fonction pour déterminer la priorité des opérateurs
int precedence(char operator) {
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

// Fonction pour gérer un opérateur
void handleOperator(Stack* operatorStack, char operator, char* output, int* outputIndex) {
    while (!isEmpty(operatorStack) && precedence((char)operatorStack->items[operatorStack->top]) >= precedence(operator)) {
        output[(*outputIndex)++] = (char)pop(operatorStack);
        output[(*outputIndex)++] = ' ';
    }
    push(operatorStack, operator);
}

// Fonction pour ignorer les espaces
void skipSpaces(const char* expression, int* i) {
    while (isspace(expression[*i])) {
        (*i)++;
    }
}

// Fonction pour traiter un caractère de l'expression
void processCharacter(const char* expression, int* i, Stack* operatorStack, char* output, int* outputIndex) {
    if (isdigit(expression[*i])) {
        addOperandToOutput(expression, i, output, outputIndex);
    } else if (expression[*i] == '(') {
        push(operatorStack, expression[*i]);
    } else if (expression[*i] == ')') {
        handleClosingParenthesis(operatorStack, output, outputIndex);
    } else if (strchr("+-*/", expression[*i])) {
        handleOperator(operatorStack, expression[*i], output, outputIndex);
    }
}

// Fonction pour vider la pile d'opérateurs dans la sortie
void emptyOperatorStack(Stack* operatorStack, char* output, int* outputIndex) {
    while (!isEmpty(operatorStack)) {
        output[(*outputIndex)++] = pop(operatorStack);
        output[(*outputIndex)++] = ' ';
    }
    output[(*outputIndex) - 1] = '\0'; // Remplacer le dernier espace par un terminateur
}

// Fonction principale pour convertir une expression infixée en postfixée
char* infixToPostfix(const char* expression) {
    Stack operatorStack;
    initStack(&operatorStack, strlen(expression));

    char* output = malloc(sizeof(char) * (strlen(expression) + 1));
    int outputIndex = 0;
    int length = strlen(expression);

    for (int i = 0; i < length; i++) {
        skipSpaces(expression, &i);
        processCharacter(expression, &i, &operatorStack, output, &outputIndex);
    }

    emptyOperatorStack(&operatorStack, output, &outputIndex);
    return output;
}

// Fonction pour évaluer une expression postfixée
double evaluatePostfix(const char* expression) {
    Stack pile;
    initStack(&pile, strlen(expression));

    const char* p = expression;

    while (*p) {
        if (isspace(*p)) {
            p++;
            continue; // Ignorer les espaces
        }

        if (isdigit(*p) || (*p == '.')) {
            char* end;
            double value = strtod(p, &end);
            push(&pile, value);
            p = end; // Avancer le pointeur
        } else if (strchr("+-*/", *p)) {
            double operand2 = pop(&pile);
            double operand1 = pop(&pile);
            double result = evaluateOperation(*p, operand1, operand2);
            push(&pile, result);
        }
        p++;
    }

    return pop(&pile); // La valeur finale est le résultat
}

// Fonction pour évaluer une opération
double evaluateOperation(char operator, double operand1, double operand2) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 == 0) {
                fprintf(stderr, "Erreur: division par zéro\n");
                exit(EXIT_FAILURE);
            }
            return operand1 / operand2;
        default:
            fprintf(stderr, "Erreur: opérateur inconnu\n");
            exit(EXIT_FAILURE);
    }
}