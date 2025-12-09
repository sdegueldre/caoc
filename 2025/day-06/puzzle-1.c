#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

array slice_problem(array lines, int from, int to) {
    array problem = {.el_size = sizeof(string)};
    for (int i = 0; i < lines.length; i++) {
        string line = ((string*)lines.els)[i];
        string slice = str_slice(line, from, to);
        arr_push(&problem, &slice);
    }
    return problem;
}

int main() {
    // string input = file_to_string("./puzzle-1.test");
    string input = file_to_string("./input");

    array lines = str_split(input, '\n');
    int line_width = ((string*)lines.els)[0].length;
    int problem_start = 0;
    array problems = {.el_size = sizeof(array)};
    for (int i = 0; i < line_width; i++) {
        int is_empty_col = 1;
        for (int j = 0; j < lines.length; j++) {
            string line = ((string*)lines.els)[j];
            if (line.chars[i] != ' ') {
                is_empty_col = 0;
                break;
            }
        }
        if (is_empty_col) {
            array problem = slice_problem(lines, problem_start, i);
            arr_push(&problems, &problem);
            problem_start = i+1;
        }
    }
    array problem = slice_problem(lines, problem_start, line_width);
    arr_push(&problems, &problem);

    double result = 0;
    for (int i = 0; i < problems.length; i++) {
        array problem = ((array*)problems.els)[i];
        char op = ((string*)problem.els)[problem.length - 1].chars[0];
        double problem_solution = op == '+' ? 0 : 1;
        for (int i = 0; i < problem.length - 1; i++) {
            string line = ((string*)problem.els)[i];
            double num = strtod(string_to_cstr(line), 0);
            if (op == '+') {
                problem_solution += num;
            } else {
                problem_solution *= num;
            }
        }
        result += problem_solution;
    }
    
    printf("Result: %lu\n", (unsigned long)result);
}
