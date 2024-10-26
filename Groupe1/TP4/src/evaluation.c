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

//int isInfixExpression(Token* tokens, int tokenCount) {
//    fprintf(stderr, "%d ;;; count: %d\n" , tokens[tokenCount - 1], tokenCount - 1);
//    // Check if the end expression token is a number or closing parenthesis
//    return tokens[tokenCount - 1].type == TOKEN_NUMBER || tokens[tokenCount - 1].type == TOKEN_CLOSING_PARENTHESIS;
//}
//
//int isPostfixExpression(Token* tokens, int tokenCount) {
//
//    // Check if the end expression token is an operator
//    return tokens[tokenCount - 1].type == TOKEN_PLUS || tokens[tokenCount - 1].type == TOKEN_MINUS ||
//           tokens[tokenCount - 1].type == TOKEN_MULTIPLY || tokens[tokenCount - 1].type == TOKEN_DIVIDE;
//}
int isInfixExpression(Token* tokens, int tokenCount) {
    if (tokenCount == 0) return 0;

   // fprintf(stderr, "1 : %d;;%d \n",lastToken.type, tokenCount);
    Token lastToken = tokens[tokenCount - 1];
    if (lastToken.type == TOKEN_NUMBER || lastToken.type == TOKEN_CLOSING_PARENTHESIS) {
        return 1; // Le dernier token est un nombre ou une parenthèse fermante -> infixe
    }

    return 0; // Sinon, ce n'est pas une expression infixe
}


int isPostfixExpression(Token* tokens, int tokenCount) {
    if (tokenCount == 0) return 0;

    Token lastToken = tokens[tokenCount - 1];
    //fprintf(stderr, "2 : %d;;%d \n",lastToken.type, tokenCount);
    if (lastToken.type != TOKEN_PLUS ||
        lastToken.type != TOKEN_MINUS ||
        lastToken.type != TOKEN_MULTIPLY ||
        lastToken.type != TOKEN_DIVIDE) {
        return 1; // Le dernier token n'est pas un opérateur -> postfixe
    }

    return 0; // Sinon, ce n'est pas une expression postfixe
}

