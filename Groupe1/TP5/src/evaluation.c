#include <ctype.h>
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
            fprintf(stderr, "expression: \n Operand1: %f\n Operand2: %f\n Operator: %c\n", expr.operand1, expr.operand2, expr.operation);
            fprintf(stderr, "Erreur d'évaluation\n");
            exit(EXIT_FAILURE);
    }
}

int isOperation(char* input) {
    //if it contains an operator or more and nomber of operand is number of operator + 1
    int operatorCount = 0;
    int operandCount = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            operatorCount++;
        } else if (isdigit(input[i])) {
            operandCount++;
        }
    }
    return operatorCount > 0 && operandCount == operatorCount + 1;
}

int isInfixExpression(Token* tokens, int tokenCount) {
    if (tokenCount == 0) return 0;

    Token lastToken = tokens[tokenCount - 2];
    if (lastToken.type == TOKEN_NUMBER || lastToken.type == TOKEN_CLOSING_PARENTHESIS) {
        return 1; // Le dernier token est un nombre ou une parenthèse fermante -> infixe
    }

    return 0; // Sinon, ce n'est pas une expression infixe
}


int isPostfixExpression(Token* tokens, int tokenCount) {
    if (tokenCount == 0) return 0;

    Token lastToken = tokens[tokenCount - 2];
    if (lastToken.type != TOKEN_PLUS ||
        lastToken.type != TOKEN_MINUS ||
        lastToken.type != TOKEN_MULTIPLY ||
        lastToken.type != TOKEN_DIVIDE) {
        return 1; // Le dernier token n'est pas un opérateur -> postfixe
    }

    return 0; // Sinon, ce n'est pas une expression postfixe
}

int isInfix(char* input) {
    int tokenCount;
    Token* tokens = tokenize(input, &tokenCount);
    int result = isInfixExpression(tokens, tokenCount);
    free(tokens);
    return result;
}

int isPostfix(char* input) {
    int tokenCount;
    Token* tokens = tokenize(input, &tokenCount);
    int result = isPostfixExpression(tokens, tokenCount);
    free(tokens);
    return result;
}
