#include <stdio.h>
#include <stdlib.h>
#include "../../utils.c"

typedef struct problem_t {
    char op;
    array nums;
} problem_t;

problem_t slice_problem(array lines, int from, int to) {
    problem_t problem = { .op = ((string*)lines.els)[lines.length - 1].chars[from], { .el_size = sizeof(double)}};
    for (int i = from; i < to; i++) {
        char *num_str = calloc(sizeof(char), lines.length);
        for (int j = 0; j < lines.length - 1; j++) {
            num_str[j] = ((string*)lines.els)[j].chars[i];
        }
        num_str[lines.length - 1] = '\0';
        double num = strtod(num_str, 0);
        arr_push(&problem.nums, &num);
    }
    return problem;
}

int main() {
    // string input = file_to_string("./puzzle-2.test");
    string input = file_to_string("./input");

    array lines = str_split(input, '\n');
    int line_width = ((string*)lines.els)[0].length;
    int problem_start = 0;
    array problems = {.el_size = sizeof(problem_t)};
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
            problem_t problem = slice_problem(lines, problem_start, i);
            arr_push(&problems, &problem);
            problem_start = i+1;
        }
    }
    problem_t problem = slice_problem(lines, problem_start, line_width);
    arr_push(&problems, &problem);

    double result = 0;
    for (int i = 0; i < problems.length; i++) {
        problem_t problem = ((problem_t*)problems.els)[i];
        double problem_solution = problem.op == '+' ? 0 : 1;
        for (int i = 0; i < problem.nums.length; i++) {
            double num = ((double*)problem.nums.els)[i];
            if (problem.op == '+') {
                problem_solution += num;
            } else {
                problem_solution *= num;
            }
        }
        result += problem_solution;
    }
    
    printf("Result: %lu\n", (unsigned long)result);
}
