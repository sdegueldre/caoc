#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

int main() {
    // string input = file_to_string("./puzzle-1.test");
    string input = file_to_string("./input");

    int neighbors[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    array lines = str_split(input, '\n');
    unsigned long accessible = 0;
    for (int i = 0; i < lines.length; i++) {
        string line = ((string*)lines.els)[i];
        for (int j = 0; j < line.length; j++) {
            int adjacent_rolls = 0;
            if (line.chars[j] != '@') continue;
            for (int n = 0; n < 8; n++) {
                int y = neighbors[n][0] + i;
                int x = neighbors[n][1] + j;
                if (x < 0 || x >= line.length) continue;
                if (y < 0 || y >= lines.length) continue;
                adjacent_rolls += ((string*)lines.els)[y].chars[x] == '@';
            }
            if (adjacent_rolls < 4) {
                accessible++;
            }
        }
    }
    
    printf("Result: %lu\n", (unsigned long)accessible);
}
