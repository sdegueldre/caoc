#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int main() {
    string input = file_to_string("./puzzle-1.test");
    // string input = file_to_string("./input");

    array lines = str_split(input, '\n');
    double result = 0;
    
    printf("Result: %lu\n", (unsigned long)result);
}
