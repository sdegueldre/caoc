#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int sort_ranges(const void *_left, const void *_right) {
    const double *left = _left;
    const double *right = _right;
    return right[0] - left[0] < 0;
}

int main() {
    // string input = file_to_string("./puzzle-1.test");
    string input = file_to_string("./input");

    array parts = str_split_str(input, string_from_cstr("\n\n"));
    array range_strings = str_split(((string*)parts.els)[0], '\n');

    array ranges = {.el_size = sizeof(double[2])};
    for (int i = 0; i < range_strings.length; i++) {
        string range_string = ((string*)range_strings.els)[i];
        array range_parts = str_split(range_string, '-');
        char *left = string_to_cstr(((string*)range_parts.els)[0]);
        char *right = string_to_cstr(((string*)range_parts.els)[1]);
        double range[2] = {strtod(left, 0), strtod(right, 0)};
        arr_push(&ranges, &range);
    }

    qsort(ranges.els, ranges.length, sizeof(double[2]), sort_ranges);
    
    array merged_ranges = {.el_size = sizeof(double[2])};
    double *current_range = ((double(*)[2])ranges.els)[0];
    for (int i = 1; i < ranges.length; i++) {
        double *range = ((double(*)[2])ranges.els)[i];
        if (current_range[0] <= range[0] && range[0] <= current_range[1]) {
            printf("merging ranges [%llu, %llu] and [%llu, %llu]\n", (unsigned long long)current_range[0], (unsigned long long)current_range[1], (unsigned long long)range[0], (unsigned long long)range[1]);
            current_range[1] = range[1] > current_range[1] ? range[1] : current_range[1];
        } else {
            arr_push(&merged_ranges, current_range);
            current_range = range;
        }
    }
    arr_push(&merged_ranges, current_range);

    double fresh = 0;
    for (int i = 0; i < merged_ranges.length; i++) {
        double *range = ((double(*)[2])merged_ranges.els)[i];
        fresh += range[1] - range[0] + 1;
    }
    
    printf("Result: %llu\n", (unsigned long long)fresh);
}
