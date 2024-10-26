#include <stdio.h>
#include <string.h>

char* VERSION = "1.0";
int CONTINUE = 1;

enum lang {
    FR,
    EN
};

typedef enum lang Lang;

typedef struct {
    char* nom_FR;
    char* nom_EN;
} Nom;

// Structure pour la description
typedef struct {
    char* description_FR;
    char* description_EN;
} Description;

// Structure pour les commandes
typedef struct {
    Nom nom;
    Description description;
    void (*fonction)(Lang, char*);
} Commande;

// Function declarations
void traiter_echo(Lang lang, char* commande);
void traiter_quit(Lang lang, char* unused);
void afficher_aide(Lang lang, char* unused);
void afficher_version(Lang lang, char* unused);
void corriger_commande(char* commande);
void afficher_date(Lang lang, char* unused);

//tableau de commandes
Commande commandes[] = {
    {
        {"echo","echo"},
        {"Afficher du texte dans l'interpréteur", "Display text in the REPL"},
        traiter_echo},
    {
        {"quitter","quit"},
        {"Quitter l'interpréteur", "Exit the REPL"},
        traiter_quit},
    {
        {"aide","help"},
        {"Afficher l'aide de l'interpréteur", "Display the help of the REPL"},
        afficher_aide},
    {
        {"version","version"},
        {"Afficher la version de l'interpréteur", "Display the version of the REPL"},
        afficher_version},
    {
        {"date","date"},
        {"Afficher la date et l'heure actuelles", "Display the current date and time"},
        afficher_date},
    {
        {NULL, NULL},
        {NULL, NULL},
        NULL}

};

void traiter_echo(Lang lang, char* commande) {
    // Traite la commande "echo" pour afficher du texte
    if (commande[5] == '\0') {
        printf("%s\n", lang == FR ? "Erreur: la commande 'echo' nécessite un argument" : "Error: 'echo' command requires an argument");
    } else {
        printf("%s\n", lang == FR ? "Texte à afficher:" : "Text to display:");
        printf("%s\n", &commande[5]);
    }
}

void traiter_quit(Lang lang, char* unused) {
    printf("%s\n", lang == FR ? "Au revoir!" : "Goodbye!");
    CONTINUE = 0;
}

void afficher_aide(Lang lang, char* unused) {
    printf("%s\n", lang == FR ? "Liste des commandes:" : "List of commands:");
    for (int i = 0; commandes[i].nom.nom_FR != NULL; i++) {
        printf("%s: %s\n", lang == FR ? commandes[i].nom.nom_FR : commandes[i].nom.nom_EN,
               lang == FR ? commandes[i].description.description_FR : commandes[i].description.description_EN);
    }
}

void afficher_version(Lang lang, char* unused) {
    printf("%s: %s\n", lang == FR ? "Version" : "Version", VERSION);
}

void afficher_mauvaise_commande(Lang lang, char* commande) {
        corriger_commande(commande);
}

void corriger_commande(char* commande) {
    // Donne la commande ressemblant le plus à la commande entrée
    int min = 100;
    char* commande_corrige = NULL;
    Lang lang = FR;
    for (int i = 0; commandes[i].nom.nom_FR != NULL; i++) {
        int diff = strcmp(commandes[i].nom.nom_FR, commande);
        if (diff < min) {
            min = diff;
            commande_corrige = commandes[i].nom.nom_FR;
        }
        diff = strcmp(commandes[i].nom.nom_EN, commande);
        if (diff < min) {
            min = diff;
            commande_corrige = commandes[i].nom.nom_EN;
            lang = EN;
        }
    }
    printf("%s %s %s %s\n",
    lang == FR ? "Commande non reconnue, voulez-vous dire" : "Command not recognized, did you mean",
    commande_corrige, "? \n",
    lang == FR ? "Essayez 'aide' pour obtenir de l'aide." : "Try 'help' for help.");
}

void afficher_date(Lang lang, char* unused) {
    printf("%s " __DATE__ " " __TIME__, lang == FR ? "Date et heure actuelles:" : "Current date and time:");
}

char* set_commande(){
    static char commande[1024];

    // Lit la commande utilisateur et la stocke dans le buffer
    fgets(commande, sizeof(commande), stdin);

    // Enlève le caractère de fin de ligne ajouté par fgets
    commande[strcspn(commande, "\n")] = 0;

    return commande;
}

void traiter_commande(char* commande){
    char* cmd = strtok(commande, " ");
    for (int i = 0; commandes[i].nom.nom_FR != NULL; i++) {
        if (strcmp(commandes[i].nom.nom_FR, commande) == 0 || strcmp(commandes[i].nom.nom_EN, commande) == 0) {
            commandes[i].fonction(strcmp(commandes[i].nom.nom_FR, commande) == 0 ? FR : EN, commande);
            return;
        }
    }
    // Affiche un message d'erreur si la commande n'est pas reconnue, FR est par défaut mais dans tout les cas, le message est dans les deux langues
    afficher_mauvaise_commande(FR, commande);
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
        printf("\n> "); // Affiche le prompt de commande

        // Buffer pour stocker la commande utilisateur
        char* commande = set_commande();

        // Traite la commande en fonction de son contenu
        traiter_commande(commande);

    }

    return 0;
}
