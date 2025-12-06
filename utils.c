#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct string {
  size_t length;
  char* chars;
} string;

typedef struct array {
  size_t length;
  size_t el_size;
  size_t capacity;
  void* els;
} array;

void arr_push(array* arr, void* el) {
  if (arr->length >= arr->capacity) {
    arr->capacity = (arr->capacity ? arr->capacity : 7.0f) * 1.5f;
    arr->els = realloc(arr->els, arr->capacity * arr->el_size);
  }
  memcpy(&((char*)arr->els)[arr->length++ * arr->el_size], el, arr->el_size);
}

string string_from_cstr(char* cstr) {
  const size_t length = strlen(cstr);
  const string ret = { .length = length, .chars = cstr }; 
  return ret;
}

string str_slice(string str, ptrdiff_t from, ptrdiff_t to) {
  if (from < 0) {
    from = str.length - from;
  }
  if (to < 0) {
    to = str.length - to;
  }
  to = to > str.length ? str.length : to;
  const string ret = { .length = to - from, .chars = &str.chars[from]};
  return ret;
}

array str_split(string str, char delimiter) {
  array string_arr = {.length = 0, .el_size = sizeof(string)};
  size_t slice_start = 0;
  for (size_t current_idx = 0; current_idx < str.length; current_idx++) {
    if (str.chars[current_idx] == delimiter) {
      string slice = str_slice(str, slice_start, current_idx);
      arr_push(&string_arr, &slice);
      slice_start = current_idx + 1;
    }
  }
  string slice = str_slice(str, slice_start, str.length);
  arr_push(&string_arr, &slice);
  return string_arr;
}

char* string_to_cstr(string str) {
  char* cstr = malloc((str.length + 1) * sizeof(char));
  memcpy(cstr, str.chars, str.length);
  cstr[str.length] = '\0';
  return cstr;
}

string file_to_string(char* fname) {
  FILE* input = fopen(fname, "r");

  fseek(input, 0, SEEK_END);
  long fsize = ftell(input);
  fseek(input, 0, SEEK_SET);

  string ret = { .length = fsize, .chars = malloc(fsize)};
  fread(ret.chars, fsize, 1, input);
  fclose(input);

  return ret;
}