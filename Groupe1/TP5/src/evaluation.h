#ifndef EVALUATION_H
#define EVALUATION_H

#include "parseur.h"

double evaluate(Expression expr);

int isOperation(char* input);
int isInfixExpression(Token* tokens, int tokenCount);
int isPostfixExpression(Token* tokens, int tokenCount);
int isInfix(char* input);
int isPostfix(char* input);

#endif // EVALUATION_H
