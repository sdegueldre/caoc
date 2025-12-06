#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int is_invalid(double num) {
    char buff[80];
    snprintf(buff, 80, "%lu", (unsigned long)num);
    string str = string_from_cstr(buff);
    if (str.length % 2) return 0;
    size_t half = str.length / 2;
    string left = str_slice(str, 0, half);
    string right = str_slice(str, half, str.length);
    return memcmp(left.chars, right.chars, half) == 0;
}

int main() {
    // string input = file_to_string("./puzzle-1.test");
    string input = file_to_string("./input");

    array ranges = str_split(input, ',');
    double invalid_sum = 0;
    for (size_t i = 0; i < ranges.length; i++) {
        array range =  str_split(((string*)ranges.els)[i], '-');
        double from = strtod(((string*)range.els)[0].chars, 0);
        double to = strtod(((string*)range.els)[1].chars, 0);
        for (double i = from; i <= to; i++) {
            invalid_sum += is_invalid(i) ? i : 0;
        }
    }
    printf("Invalid sum: %lu\n", (unsigned long)invalid_sum);
}
