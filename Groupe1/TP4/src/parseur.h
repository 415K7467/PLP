#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

typedef struct {
    TokenType operation;
    double operand1;
    double operand2;
} Expression;

Expression parse(Token* tokens, int tokenCount);

#endif // PARSER_H
