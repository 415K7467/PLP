#ifndef REPL_H
#define REPL_H

extern int CONTINUE;

char* set_commande();
void traiter_commande(char* commande);
void handleInfixExpression(const char* expression);
void handlePostfixExpression(const char* expression);

#endif // REPL_H