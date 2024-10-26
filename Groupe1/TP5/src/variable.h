#ifndef VARIABLE_H
#define VARIABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VARIABLES 100
#define MAX_NAME_LENGTH 256

typedef enum {
    INT,
    FLOAT,
    STRING,
    UNDEFINED
} VarType;

typedef struct {
    char name[MAX_NAME_LENGTH];
    VarType type;
    char value[MAX_NAME_LENGTH];
} Variable;

typedef struct {
    Variable variables[MAX_VARIABLES];
    int count;
} SymbolTable;

// Function prototypes
void initSymbolTable(SymbolTable *table);
bool assignVariable(SymbolTable *table, const char *name, const char *value);
bool getVariable(const SymbolTable *table, const char *name);
void printVariable(const Variable *var);
const char* typeToString(VarType type);

#endif // VARIABLE_H
