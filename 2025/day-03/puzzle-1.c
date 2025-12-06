#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int main() {
    string input = file_to_string("./puzzle-1.test");
    // string input = file_to_string("./input");

    array lines = str_split(input, '\n');
    array banks = {.el_size = sizeof(array)};
    for (int i = 0; i < lines.length; i++) {
        string line = ((string*)lines.els)[i];
        array* bank = calloc(1, sizeof *bank);
        bank->el_size = sizeof(int);
        for (int j = 0; j < line.length; j++) {
            int digit = ((int)(line.chars[j] - '0'));
            arr_push(bank, &digit);
            printf("Bank length: %lu\n", bank->length);
        }
        arr_push(&banks, bank);
    }
    printf("\nBanks length: %lu\n", banks.length);
    for (int i = 0; i < banks.length; i++) {
        array bank = ((array*)banks.els)[i];
        printf("Bank length: %lu\n", bank.length);
        for (int j = 0; j < bank.length; j++) {
            printf("%d", ((int*)bank.els)[j]);
        }
        printf("\n");
    }
    double result = 0;
    
    printf("Result: %lu\n", (unsigned long)result);
}
