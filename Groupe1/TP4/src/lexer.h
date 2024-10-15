#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_END,
    TOKEN_ERROR
} TokenType;

typedef struct {
    TokenType type;
    double value; // Utilisé pour les nombres
} Token;

Token* tokenize(const char* expression, int* tokenCount);

#endif // LEXER_H
