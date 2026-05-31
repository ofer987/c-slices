#include "string_array.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ArraySlice {
  bool is_empty;
  char* value;
  size_t length;
  size_t capacity;
};

size_t
get_length(struct ArraySlice* s) {
  return s->length;
}

size_t
get_capacity(struct ArraySlice* s) {
  return s->capacity;
}

char*
get_value(struct ArraySlice* s) {
  return s->value;
}

bool
is_empty(struct ArraySlice* s) {
  return s->is_empty;
}

struct Result {
  struct ArraySlice* array_slice;
  char* error_message;
  bool is_success;
};

bool
is_success(struct Result* result) {
  return result->is_success;
}

char*
get_error_message(struct Result* result) {
  return result->error_message;
}

struct ArraySlice*
get_array_slice(struct Result* result) {
  return result->array_slice;
}

void
free_result(struct Result* result) {
  free(result);
}

void
free_string_array(struct ArraySlice* result) {
  free(result->value);
  free(result);
}

struct ArraySlice*
add_capacity(struct ArraySlice* smaller_array, size_t new_capacity) {
  if (new_capacity <= smaller_array->capacity) {
    return NULL;
  }

  struct ArraySlice* larger_array = make_string_array(smaller_array->value, new_capacity);

  free_string_array(smaller_array);

  return larger_array;
}

struct Result*
copy_into_array_slice(size_t starting_value, char* existing_value, struct ArraySlice* destination) {
  if (existing_value == NULL) {
    struct Result* result = malloc(sizeof(struct Result));
    // clang-format off
    *result = (struct Result) {
      .array_slice = destination,
      .error_message = NULL,
      .is_success = true
    };
    // clang-format on

    return result;
  }

  size_t length_of_existing_value = strlen(existing_value);
  size_t new_length = starting_value + length_of_existing_value;
  if (new_length > destination->capacity) {
    size_t new_capacity = new_length * 2;
    destination = add_capacity(destination, new_capacity);

    if (destination == NULL) {
      struct Result* failure = malloc(sizeof(struct Result));
      // clang-format off
      *failure = (struct Result) {
        .error_message = "Capacity is not large enough",
        .is_success = false,
        .array_slice = destination
      };
      // clang-format on

      return failure;
    }
  }

  memcpy(destination->value + starting_value, existing_value, length_of_existing_value);

  // Add the \0 terminator
  size_t null_terminator_index = starting_value + length_of_existing_value;
  destination->value[null_terminator_index] = '\0';
  destination->length = null_terminator_index;
  destination->is_empty = false;

  struct Result* result = malloc(sizeof(struct Result));
  // clang-format off
  *result = (struct Result) {
    .array_slice = destination,
    .error_message = NULL,
    .is_success = true
  };
  // clang-format on

  return result;
}

struct ArraySlice*
make_string_array(char* existing_value, size_t capacity) {
  if (capacity == 0) {
    printf("Capacity cannot be 0!\n");

    return NULL;
  }

  // Account for the \0 terminator
  char* fully_allocated_memory = malloc(capacity + 1);
  struct ArraySlice* result = malloc(sizeof(struct ArraySlice));

  result->value = fully_allocated_memory;
  result->is_empty = true;
  result->capacity = capacity;
  result->length = 0;

  struct Result* message = copy_into_array_slice(0, existing_value, result);
  if (!is_success(message)) {
    printf("%s\n", get_error_message(message));

    free_result(message);

    return NULL;
  }

  free_result(message);

  return result;
}

struct ArraySlice*
append_string_array(struct ArraySlice* array_slice, char* new_value) {
  struct Result* result = copy_into_array_slice(array_slice->length, new_value, array_slice);

  if (!is_success(result)) {
    printf("%s\n", get_error_message(result));

    free_result(result);

    return NULL;
  }

  struct ArraySlice* array = get_array_slice(result);

  free_result(result);

  return array;
}

size_t
my_strlen(const char* string) {
  if (string == NULL) {
    printf("string is NULL\n");

    exit(EXIT_FAILURE);
  }

  size_t result = 0;
  for (; string[result] != '\0'; result += 1) {}

  return result;
}
