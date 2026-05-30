#include "string_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
free_string_array(struct ArraySlice* result) {
  free(result->value);
  free(result);

  return;
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

struct Result
copy_into_array_slice(size_t starting_value, char* existing_value, struct ArraySlice* destination) {
  if (existing_value == NULL) {
    struct Result result = {.array_slice = destination, .error_message = NULL, .is_success = true};
    return result;
  }

  size_t length_of_existing_value = strlen(existing_value);
  size_t new_length = starting_value + length_of_existing_value;
  if (new_length > destination->capacity) {
    destination = add_capacity(destination, destination->capacity * 2);

    if (destination == NULL) {
      struct Result failure_message = {
        .error_message = "Capacity is not large enough",
        .is_success = false,
        .array_slice = destination};

      return failure_message;
    }
  }

  memcpy(destination->value + starting_value, existing_value, length_of_existing_value);

  // Add the \0 terminator
  size_t null_terminator_index = starting_value + length_of_existing_value;
  destination->value[null_terminator_index] = '\0';
  destination->length = null_terminator_index;
  destination->is_empty = false;

  struct Result result = {.array_slice = destination, .error_message = NULL, .is_success = true};
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

  struct Result message = copy_into_array_slice(0, existing_value, result);
  if (!message.is_success) {
    printf("%s\n", message.error_message);

    return NULL;
  }

  return result;
}

struct ArraySlice*
append_string_array(struct ArraySlice* array_slice, char* new_value) {
  struct Result result = copy_into_array_slice(array_slice->length, new_value, array_slice);

  if (!result.is_success) {
    printf("%s\n", result.error_message);

    return NULL;
  }

  return result.array_slice;
}

size_t
my_strlen(char* string) {
  if (string == NULL) {
    printf("string is NULL\n");

    exit(EXIT_FAILURE);
  }

  size_t result = 0;
  for (; string[result] != '\0'; result += 1) {}

  return result;
}
