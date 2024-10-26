#include <stdio.h>
#include <stdlib.h>
#include "parseur.h"

Expression parse(Token* tokens, int tokenCount) {
    Expression expr;
    int index = 0;
    int operatorCount = 0;

    if (index < tokenCount && tokens[index].type == TOKEN_NUMBER) {
        expr.operand1 = tokens[index++].value;
    } else {
        fprintf(stderr, "Erreur de syntaxe: premier opérande attendu\n");
        exit(EXIT_FAILURE);
    }

    while (index < tokenCount && tokens[index].type != TOKEN_END) {
        if (tokens[index].type == TOKEN_PLUS || tokens[index].type == TOKEN_MINUS ||
            tokens[index].type == TOKEN_MULTIPLY || tokens[index].type == TOKEN_DIVIDE) {
            if (operatorCount > 0) {
                fprintf(stderr, "Erreur de syntaxe: plusieurs opérateurs détectés\n");
                exit(EXIT_FAILURE);
            }
            expr.operation = tokens[index].type;
            operatorCount++;
        } else if (tokens[index].type == TOKEN_NUMBER) {
            if (operatorCount == 0) {
                fprintf(stderr, "Erreur de syntaxe: opérateur attendu avant le second opérande\n");
                exit(EXIT_FAILURE);
            }
            expr.operand2 = tokens[index].value;
        } else {
            fprintf(stderr, "Erreur de syntaxe: token inattendu\n");
            exit(EXIT_FAILURE);
        }
        index++;
    }

    if (operatorCount == 0) {
        fprintf(stderr, "Erreur de syntaxe: opérateur manquant\n");
        exit(EXIT_FAILURE);
    }

    return expr;
}