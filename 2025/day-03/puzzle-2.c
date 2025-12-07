#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int main() {
    // string input = file_to_string("./puzzle-2.test");
    string input = file_to_string("./input");

    array lines = str_split(input, '\n');
    array banks = {.el_size = sizeof(array*)};
    for (int i = 0; i < lines.length; i++) {
        string line = ((string*)lines.els)[i];
        array *bank = calloc(1, sizeof *bank);
        bank->el_size = sizeof(int);
        arr_push(&banks, &bank);
        for (int j = 0; j < line.length; j++) {
            int digit = ((int)(line.chars[j] - '0'));
            arr_push(bank, &digit);
        }
    }
    unsigned long joltage = 0;
    for (int i = 0; i < banks.length; i++) {
        array bank = *((array**)banks.els)[i];
        int digits[12] = {0};
        for (int j = 0; j < bank.length; j++) {
            int digit = ((int*)bank.els)[j];
            for (int k = 0; k < 12; k++) {
                if (digit > digits[k] && j <= bank.length - (12 - k)) {
                    digits[k] = digit;
                    for (int m = k + 1; m < k + 11; m++) {
                        digits[m] = 0;
                    }
                    break;
                }
            }
        }
        char joltage_str[13];
        joltage_str[12] = '\0';
        for (int j = 0; j < 12; j++) {
            joltage_str[j] = '0' + digits[j];
        }
        joltage += atoll(joltage_str);
    }
    
    printf("Result: %lu\n", joltage);
}
