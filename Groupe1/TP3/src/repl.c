#include <stdio.h>
#include <string.h>

char* VERSION = "1.0";
int CONTINUE = 1;

struct Commande {
    char* nom;
    void (*fonction)();
    char* description;
};

// Function declarations
void traiter_echo(char commande[1024]);
void traiter_quit();
void afficher_aide();
void afficher_version();
void afficher_date();

//tableau de commandes
struct Commande commandes[] = {
    {"echo", traiter_echo, "Afficher du texte dans l'interpréteur"},
    {"quit", traiter_quit, "Quitter l'interpréteur"},
    {"quitter", traiter_quit, "Quitter l'interpréteur"},
    {"help", afficher_aide, "Afficher l'aide de l'interpréteur"},
    {"aide", afficher_aide, "Afficher l'aide de l'interpréteur"},
    {"version", afficher_version, "Afficher la version de l'interpréteur"},
    {"date", afficher_date, "Afficher la date et l'heure actuelles"}
};

void traiter_echo(char commande[1024]) {
    // Traite la commande "echo" pour afficher du texte
    printf("Echo: ");

    // Imprime la chaîne
    for (int i = 5; commande[i] != '\0'; i++)
    {
        printf("%c", commande[i]);
    }
    printf("\n"); // Saut de ligne après la sortie
}

void traiter_quit() {
    // Quitte le programme si la commande est "quit"
    printf("Arrêt...\n");
    CONTINUE = 0;
}

void afficher_aide() {
    printf("Liste des commandes:\n");
    for (int i = 0; i < sizeof(commandes) / sizeof(commandes[0]); i++) {
        printf("%s : %s\n", commandes[i].nom, commandes[i].description);
    }
}

void afficher_version() {
    printf("version: %s", VERSION);
}

void afficher_commande_vide() {
   printf("Commande vide, veuillez entrer une commande.\n");
}

void afficher_date()
{
    // Affiche la date et l'heure actuelles
    printf("Date et heure actuelles: " __DATE__ " " __TIME__ "\n");
}


/**
 * Programme qui simule un interpréteur de commandes simple.
 * Il lit les commandes utilisateur et les traite en fonction de leur contenu.
 */

int main()
{

    // Boucle principale qui lit et traite les commandes utilisateur
    while (CONTINUE)
    {
        printf("> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char commande[1024];

        // Lit la commande utilisateur et la stocke dans le buffer
        fgets(commande, sizeof(commande), stdin);

        // Enlève le caractère de fin de ligne ajouté par fgets
        commande[strcspn(commande, "\n")] = 0;

        // Traite la commande en fonction de son contenu
        if (strcmp(commande, "quit") == 0)
        {
            traiter_quit();
        }
        else if (strcmp(commande, "quitter") == 0){
            traiter_quit();
        }
        else if (strncmp(commande, "echo ", 5) == 0)
        {
            traiter_echo(commande);
        }
        else if (strcmp(commande, "help") == 0) {
            afficher_aide();
        }
        else if (strcmp(commande, "aide") == 0) {
            afficher_aide();
        }
        else if (strcmp(commande, "version") == 0) {
            afficher_version();
        }
        else if (strcmp(commande, "date") == 0)
        {
           afficher_date();
        }
        else if (strcmp(commande, "") == 0)
        {
           afficher_commande_vide();
        }
        else
        {
            // Affiche un message d'erreur si la commande est inconnue
            printf("Commande non reconnue. Essayez 'echo <text>' pour afficher du texte, ou tapez 'quit' pour quitter.\n");
        }

        printf("\n"); // Saut de ligne après la sortie
    }

    return 0;
}
