#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"

// gcc -o interpreter main.c lexer.c parseur.c evaluation.c -lm

int main() {
    char expression[100];
    printf("Entrez une expression mathématique : ");
    fgets(expression, sizeof(expression), stdin);

    int tokenCount;
    Token* tokens = tokenize(expression, &tokenCount);
    Expression expr = parse(tokens, tokenCount);
    double result = evaluate(expr);

    printf("Résultat : %.2f\n", result);

    free(tokens);
    return 0;
}
