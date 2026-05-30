#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct ArraySlice ArraySlice;

size_t
get_length(struct ArraySlice* s);

size_t
get_capacity(struct ArraySlice* s);

char*
get_value(struct ArraySlice* s);

bool
is_empty(struct ArraySlice* s);

struct Result {
  struct ArraySlice* array_slice;
  char* error_message;
  bool is_success;
};

struct ArraySlice*
make_string_array(char* existing_value, size_t capacity);

void
free_string_array(struct ArraySlice* result);

struct ArraySlice*
add_capacity(struct ArraySlice* smaller_array, size_t new_capacity);

struct Result
copy_into_array_slice(size_t starting_value, char* existing_value, struct ArraySlice* destination);

struct ArraySlice*
append_string_array(struct ArraySlice* array_slice, char* new_value);

size_t
my_strlen(char* string);
