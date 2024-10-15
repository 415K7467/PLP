#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexer.h"

static Token createToken(TokenType type, double value) {
    Token token;
    token.type = type;
    token.value = value;
    return token;
}

Token* tokenize(const char* expression, int* tokenCount) {
    Token* tokens = malloc(sizeof(Token) * 100); // Allocation initiale
    *tokenCount = 0;

    const char* p = expression;
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (isdigit(*p) || (*p == '.')) { // Nombres
            char* end;
            double value = strtod(p, &end);
            tokens[(*tokenCount)++] = createToken(TOKEN_NUMBER, value);
            p = end;
        } else if (*p == '+') {
            tokens[(*tokenCount)++] = createToken(TOKEN_PLUS, 0);
            p++;
        } else if (*p == '-') {
            tokens[(*tokenCount)++] = createToken(TOKEN_MINUS, 0);
            p++;
        } else if (*p == '*') {
            tokens[(*tokenCount)++] = createToken(TOKEN_MULTIPLY, 0);
            p++;
        } else if (*p == '/') {
            tokens[(*tokenCount)++] = createToken(TOKEN_DIVIDE, 0);
            p++;
        } else {
            tokens[(*tokenCount)++] = createToken(TOKEN_ERROR, 0);
            break; // Erreur
        }
    }
    tokens[(*tokenCount)++] = createToken(TOKEN_END, 0); // Fin des tokens

    return tokens;
}
