#include "variable.h"

// Initialize the symbol table
void initSymbolTable(SymbolTable *table) {
    table->count = 0;
}

// Convert VarType to string for display
const char* typeToString(VarType type) {
    switch (type) {
        case INT: return "entier";
        case FLOAT: return "nombre réel";
        case STRING: return "chaîne de caractères";
        default: return "non défini";
    }
}

// Determine the type of a value
VarType determineType(const char *value) {
    int intValue;
    float floatValue;

    if (sscanf(value, "%d", &intValue) == 1) {
        return INT;
    } else if (sscanf(value, "%f", &floatValue) == 1) {
        return FLOAT;
    } else {
        return STRING;
    }
}

// Assign a value to a variable
bool assignVariable(SymbolTable *table, const char *name, const char *value) {
    // Check if the variable already exists
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->variables[i].name, name) == 0) {
            // Check the type
            VarType currentType = table->variables[i].type;
            VarType newType = determineType(value);

            // Check for type change
            if (currentType != UNDEFINED && currentType != newType) {
                printf("Erreur : changement de type non autorisé pour la variable %s\n", name);
                return false;
            }

            // Update variable
            table->variables[i].type = newType;
            strncpy(table->variables[i].value, value, MAX_NAME_LENGTH - 1);
            table->variables[i].value[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
            return true;
        }
    }

    // If the variable doesn't exist, create a new one
    if (table->count < MAX_VARIABLES) {
        strncpy(table->variables[table->count].name, name, MAX_NAME_LENGTH - 1);
        table->variables[table->count].name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination

        // Determine the type of the new variable
        VarType newType = determineType(value);

        table->variables[table->count].type = newType;
        strncpy(table->variables[table->count].value, value, MAX_NAME_LENGTH - 1);
        table->variables[table->count].value[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
        table->count++;
        printf("Variable %s définie avec la valeur %s (%s)\n", name, value, typeToString(newType));
        return true;
    }

    printf("Erreur : nombre maximum de variables atteint.\n");
    return false;
}

// Retrieve and print a variable
bool getVariable(const SymbolTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->variables[i].name, name) == 0) {
            printVariable(&table->variables[i]);
            return true;
        }
    }
    printf("Erreur : la variable %s n'est pas définie\n", name);
    return false;
}

// Print variable details
void printVariable(const Variable *var) {
    printf("Variable %s a pour valeur %s (%s)\n", var->name, var->value, typeToString(var->type));
}
