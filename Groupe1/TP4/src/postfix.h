#ifndef POSTFIX_H
#define POSTFIX_H

#include "pile.h" // Inclue pile.h pour pouvoir utiliser la structure Stack

// Function declarations
void addOperandToOutput(const char* expression, int* i, char* output, int* outputIndex);
void handleClosingParenthesis(Stack* operatorStack, char* output, int* outputIndex);
int precedence(char operator);
void handleOperator(Stack* operatorStack, char operator, char* output, int* outputIndex);
double evaluateOperation(char operator, double operand1, double operand2);

char* infixToPostfix(const char* expression);
double evaluatePostfix(const char* expression);

#endif // POSTFIX_H
