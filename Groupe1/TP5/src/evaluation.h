#ifndef EVALUATION_H
#define EVALUATION_H

#include "parseur.h"

double evaluate(Expression expr);
int isInfixExpression(Token* tokens, int tokenCount);
int isPostfixExpression(Token* tokens, int tokenCount);

#endif // EVALUATION_H
