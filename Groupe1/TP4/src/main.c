#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"
#include "postfix.h"

// gcc -o interpreter main.c lexer.c parseur.c evaluation.c -lm

// int main() {
//     char expression[100];
//     printf("Entrez une expression mathématique : ");
//     fgets(expression, sizeof(expression), stdin);

//     int tokenCount;
//     Token* tokens = tokenize(expression, &tokenCount);
//     Expression expr = parse(tokens, tokenCount);
//     double result = evaluate(expr);

//     printf("Résultat : %.2f\n", result);

//     free(tokens);
//     return 0;
// }

// gcc -o converter main.c postfix.c pile.c

int main() {
    char expression[100];
    printf("Entrez une expression mathématique en notation infixée : ");
    fgets(expression, sizeof(expression), stdin);

    char* postfix = infixToPostfix(expression);
    printf("Notation postfixée : %s\n", postfix);
    printf("Résultat : %.2f\n", evaluatePostfix(postfix));
    free(postfix);
    return 0;
}

// gcc -o evaluator main.c postfix.c pile.c -lm

// int main() {
//     char expression[100];
//     printf("Entrez une expression mathématique en notation postfixée : ");
//     fgets(expression, sizeof(expression), stdin);

//     double result = evaluatePostfix(expression);
//     printf("Résultat : %.2f\n", result);

//     return 0;
// }
