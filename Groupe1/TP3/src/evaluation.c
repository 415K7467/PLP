#include <stdio.h>
#include <stdlib.h>
#include "evaluation.h"

double evaluate(Expression expr) {
    switch (expr.operation) {
        case TOKEN_PLUS:
            return expr.operand1 + expr.operand2;
        case TOKEN_MINUS:
            return expr.operand1 - expr.operand2;
        case TOKEN_MULTIPLY:
            return expr.operand1 * expr.operand2;
        case TOKEN_DIVIDE:
            if (expr.operand2 == 0) {
                fprintf(stderr, "Erreur: division par zéro\n");
                exit(EXIT_FAILURE);
            }
            return expr.operand1 / expr.operand2;
        default:
            fprintf(stderr, "Erreur d'évaluation\n");
            exit(EXIT_FAILURE);
    }
}
