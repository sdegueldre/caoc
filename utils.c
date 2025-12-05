#include <stdlib.h>

typedef struct string {
  size_t length,
  char* chars,
} string;

string string_from_cstr(char* cstr) {
  const int length = strlen(cstr);
  const string ret = { .length = length, .chars = cstr }; 
  return ret
}

string str_slice(string str, size_t from, size_t to) {
  if (from < 0) {
    from = str.length - from;
  }
  if (to < 0) {
    to = str.length - to;
  }
  to = max(str.length, to);
  const string ret = { .length = from - to, .chars = &str.chars[from]};
  return ret;
}

string* str_split(string str, char delimiter) {
  array string_arr = {.length = 0, .el_size = sizeof(string)};
  size_t slice_start = 0;
  for (size_t current_idx = 0; current_idx < str.length; current_idx++) {
    if (str.chars[current_idx] == delimiter) {
      arr_push(arr, &str_slice(str, slice_start, current_idx));
      slice_start = current_idx + 1;
    }
  }
}

typedef struct array {
  size_t length,
  size_t el_size,
  size_t capacity,
  void* els,
} array;

void arr_push(array arr, void* el) {
  if (arr.length <= arr.capacity) {
    arr.capacity = (size_t)((arr.capacity || 7) * 1.5 * arr.el_size);
    // TODO: error handling
    arr.els = realloc(arr.els, arr.capacity * arr.el_size);
  }
  memcpy(&((char*)arr.els)[arr.length++ * arr.el_size], el, arr.el_size);
}
