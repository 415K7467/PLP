#include "variable.h"

int main() {
    SymbolTable table;
    initSymbolTable(&table);
    char input[MAX_NAME_LENGTH + MAX_NAME_LENGTH]; // Variable name and value

    while (true) {
        printf("> ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Check for assignment
        char name[MAX_NAME_LENGTH];
        char value[MAX_NAME_LENGTH];
        if (sscanf(input, "%s = %[^\n]", name, value) == 2) {
            assignVariable(&table, name, value);
        } else {
            // Attempt to retrieve the variable
            getVariable(&table, input);
        }
    }

    return 0;
}
