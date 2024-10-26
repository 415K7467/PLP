#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_END,
    TOKEN_ERROR,
    TOKEN_OPENING_PARENTHESIS,
    TOKEN_CLOSING_PARENTHESIS
} TokenType;

typedef struct {
    TokenType type;
    double value; // Utilisé pour les nombres
} Token;

Token* tokenize(const char* expression, int* tokenCount);

#endif // LEXER_H
