#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int is_invalid(double num) {
    char buff[80];
    snprintf(buff, 80, "%lu", (unsigned long)num);
    string str = string_from_cstr(buff);
    for (int segment_size = 1; segment_size < str.length; segment_size++) {
        int continue_outer = 0;
        if (str.length % segment_size) continue; // Can't evenly divide string in segments of this size
        int i, j;
        for (i = 0; !continue_outer && i < segment_size; i++) { // check every character in the segment
            for (j = 1; !continue_outer && j < str.length / segment_size; j++) { // against every corresponding character in corresponding segments
                size_t pos = j * segment_size + i;
                if (str.chars[pos] != str.chars[i]) {
                    continue_outer = 1;
                }
            }
        }
        if (!continue_outer) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // string input = file_to_string("./puzzle-2.test");
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
