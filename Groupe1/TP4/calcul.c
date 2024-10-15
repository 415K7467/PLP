struct Tokenizer {
    String input;
    int index;
};

char* get_keyboard_input() {
    char *input = malloc(1000);
    char c;
    int i = 0;
    printf(">>> entrez un chaine de caractères à tokenizer: ");
    while (1) {
        c = getchar();
        if (c == '\n') {
            input[i] = '\0';
            break;
        }
        input[i] = c;
        i++;
    }

    //remove spaces
    input = remove_spaces(input);
    return input;
}

char* remove_spaces(char* c) {
    char* new_c = malloc(strlen(c));
    // We have list in input c with i char . When the char is not a space, we add it to the new list new_c[j]
    int j = 0;
    for (int i = 0; i < strlen(c); i++) {
        if (c[i] != ' ') {
            new_c[j] = c[i];
            j++;
        }
    }
    new_c[j] = '\0';
    return new_c;
}

bool check_arithmetic_operation(char* c) {
    string regex_rule = "[0-9]+[ ]*[-+/*][ ]*[0-9]+";
    bool is_arithmetic_operation = false;
    if (regex_match(c, regex_rule)){
        is_arithmetic_operation = true;
        for (int i = 0; i < strlen(c); i++) {
            //check if we dont have two consecutive operators, make an exception for the '-' operator (use to negate a number)
            if ((c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/')
                && (c[i+1] == '+' || c[i+1] == '*' || c[i+1] == '/')) {
                    is_arithmetic_operation = false;
                    break;
            }
        }
    };
    return is_arithmetic_operation;
}

void print_operator_and_operand(char* c) {
    char* operator_list = malloc(1);
    char *operand[] = malloc(1);
    char* tmp_operand = malloc(1);
    for (int i = 0; i < strlen(c); i++) {
        if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/') {
            // add tmp_operand to operand list and reset tmp_operand
            operand = realloc(operand, strlen(operand) + 1);
            operand[strlen(operand)] = tmp_operand;
            tmp_operand = malloc(1);

            // add operator to operator list (if not already in the list)
            if (strchr(operator_list, c[i]) == NULL) {
                operator_list = realloc(operator_list, strlen(operator_list) + 1);
                operator_list[strlen(operator_list)] = c[i];
            }
        } else {
            tmp_operand = realloc(tmp_operand, strlen(tmp_operand) + 1);
            tmp_operand[strlen(tmp_operand)] = c[i];
        }

        // print unique operator
        printf("operator: %c\n", operator_list[0]);
        // print operand with ne number of the operand (like: operand1, operand2, ...)
        for (int i = 0; i < strlen(operand); i++) {
            printf("operand%d: %s\n", i+1, operand[i]);
        }

    }
}


int main() {
    String input = get_keyboard_input(">>> entrez un chaine de caractères à tokenizer: ");
    Tokenizer tokenizer = tokenizer_create(input);
    return 0;