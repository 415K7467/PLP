#ifndef POSTFIX_H
#define POSTFIX_H

#include "pile.h" // Include pile.h for Stack structure
#include "lexer.h" // Include lexer.h for TokenType

// Function declarations
void addOperandToOutput(const char* expression, int* i, char* output, int* outputIndex);
void handleClosingParenthesis(Stack* operatorStack, char* output, int* outputIndex);
int precedence(char operator);
void handleOperator(Stack* operatorStack, char operator, char* output, int* outputIndex);
void skipSpaces(const char* expression, int* i);
void processCharacter(const char* expression, int* i, Stack* operatorStack, char* output, int* outputIndex);
void emptyOperatorStack(Stack* operatorStack, char* output, int* outputIndex);
char* infixToPostfix(const char* expression);
double evaluatePostfix(const char* expression);
double evaluateOperation(char operator, double operand1, double operand2);
TokenType getTokenOperator(char operator); // Add semicolon

#endif // POSTFIX_H