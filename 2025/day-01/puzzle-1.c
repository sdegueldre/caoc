#include <stdio.h>
#include "../../utils.c"

int main() {
    string input = file_to_string("./input");

    array lines = str_split(input, '\n');
    int dial_pos = 50;
    int zeros = 0;
    for (size_t i = 0; i < lines.length; i++) {
        string line =  ((string*)lines.els)[i];
        string slice = str_slice(line, 1, line.length);
        char* cstr = string_to_cstr(slice);
        int movement = atoi(cstr) * (line.chars[0] == 'L' ? -1 : 1) + 100;
        dial_pos = (dial_pos + movement) % 100;
        if (dial_pos == 0) {
            zeros++;
        }
    }
    printf("Zeros: %d\n", zeros);
}