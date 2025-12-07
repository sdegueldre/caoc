#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int main() {
    // string input = file_to_string("./puzzle-1.test");
    string input = file_to_string("./input");

    array parts = str_split_str(input, string_from_cstr("\n\n"));
    array range_strings = str_split(((string*)parts.els)[0], '\n');
    array ids = str_split(((string*)parts.els)[1], '\n');

    array ranges = {.el_size = sizeof(double[2])};
    for (int i = 0; i < range_strings.length; i++) {
        string range_string = ((string*)range_strings.els)[i];
        array range_parts = str_split(range_string, '-');
        char *left = string_to_cstr(((string*)range_parts.els)[0]);
        char *right = string_to_cstr(((string*)range_parts.els)[1]);
        double range[2] = {strtod(left, 0), strtod(right, 0)};
        arr_push(&ranges, &range);
    }

    unsigned long fresh = 0;
    for (int i = 0; i < ids.length; i++) {
        string id_str = ((string*)ids.els)[i];
        double id = strtod(string_to_cstr(id_str), 0);
        for (int i = 0; i < ranges.length; i++) {
            double *range = ((double(*)[2])ranges.els)[i];
            if (range[0] <= id && id <= range[1]) {
                fresh++;
                break;
            }
        }
    }
    
    printf("Result: %lu\n", (unsigned long)fresh);
}
