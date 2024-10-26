#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"
#include "postfix.h"
#include "repl.h"

// gcc -o converter main.c postfix.c pile.c lexer.c parseur.c evaluation.c repl.c -lm

/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int main()
{

    // Boucle principale qui lit et traite les commandes utilisateur
    while (CONTINUE)
    {
        printf("\n> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char* commande = set_commande();

        // Traite la commande en fonction de son contenu
        traiter_commande(commande);

    }

    return 0;
}