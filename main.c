#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_pthread/_pthread_attr_t.h>
#include <sys/_pthread/_pthread_t.h>

struct ArraySlice {
  bool is_empty;
  char *value;
  size_t length;
  size_t capacity;
};

struct Result {
  struct ArraySlice *array_slice;
  char *error_message;
  bool is_success;
};

struct ArraySlice *make_string_array(char *existing_value, size_t capacity);

void free_string_array(struct ArraySlice *result) {
  free(result->value);
  free(result);

  return;
}

struct ArraySlice *add_capacity(struct ArraySlice *smaller_array,
                                size_t new_capacity) {
  if (new_capacity <= smaller_array->capacity) {
    return NULL;
  }

  struct ArraySlice *larger_array =
      make_string_array(smaller_array->value, new_capacity);

  free_string_array(smaller_array);

  return larger_array;
}

struct Result copy_into_array_slice(size_t starting_value, char *existing_value,
                                    struct ArraySlice *destination) {
  if (existing_value == NULL) {
    struct Result result = {
        .array_slice = destination, .error_message = NULL, .is_success = true};
    return result;
  }

  size_t index = 0;

  while (existing_value[index] != '\0') {
    if (starting_value > destination->capacity) {
      destination = add_capacity(destination, destination->capacity * 2);

      if (destination == NULL) {
        struct Result failure_message = {.error_message =
                                             "Capacity is not large enough",
                                         .is_success = false,
                                         .array_slice = destination};

        return failure_message;
      }
    }

    destination->value[starting_value] = existing_value[index];

    starting_value += 1;
    index += 1;
  }

  // Add the \0 terminator
  destination->value[starting_value] = '\0';
  destination->length = starting_value;
  destination->is_empty = false;

  struct Result result = {
      .array_slice = destination, .error_message = NULL, .is_success = true};
  return result;
}

struct ArraySlice *make_string_array(char *existing_value, size_t capacity) {
  if (capacity == 0) {
    printf("Capacity cannot be 0!\n");

    return NULL;
  }

  // Account for the \0 terminator
  char *fully_allocated_memory = malloc(capacity + 1);
  struct ArraySlice *result = malloc(sizeof(struct ArraySlice));

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

struct ArraySlice *append_string_array(struct ArraySlice *array_slice,
                                       char *new_value) {
  struct Result result =
      copy_into_array_slice(array_slice->length, new_value, array_slice);

  if (!result.is_success) {
    printf("%s\n", result.error_message);

    return NULL;
  }

  return result.array_slice;
}

size_t my_strlen(char *string) {
  if (string == NULL) {
    printf("string is NULL\n");

    exit(EXIT_FAILURE);
  }

  size_t result = 0;
  for (; string[result] != '\0'; result += 1) {
  }

  return result;
}

void print_hello_world(size_t count, char *names[]) {
  if (count < 2) {
    return;
  }

  struct ArraySlice *hello_world = make_string_array("Hello", 20);

  if (count == 2) {
    hello_world = append_string_array(hello_world, " ");
    hello_world = append_string_array(hello_world, names[1]);
  } else if (count == 3) {
    hello_world = append_string_array(hello_world, " ");
    hello_world = append_string_array(hello_world, names[1]);
    hello_world = append_string_array(hello_world, " and ");
    hello_world = append_string_array(hello_world, names[2]);
  } else {
    for (size_t index = 1; index < count - 1; index += 1) {
      hello_world = append_string_array(hello_world, " ");
      hello_world = append_string_array(hello_world, names[index]);
      hello_world = append_string_array(hello_world, ",");
    }

    hello_world = append_string_array(hello_world, " and ");
    hello_world = append_string_array(hello_world, names[count - 1]);
  }

  size_t length = my_strlen(hello_world->value);

  printf("Size of hello_world is %zu and my_strlen is %zu and strlen is %zu\n",
         hello_world->length, length, strlen(hello_world->value));
  printf("hello_world is \'%s\'\n", hello_world->value);
  printf("Capacity is %zu\n", hello_world->capacity);

  return;
}

int main(int argc, char *argv[]) {
  /* char *name = "Hello World"; */
  char *another_name = "Hello World";
  /* another_name[11] = 'a'; */

  size_t foobar = 123;

  double x = 0.23f;
  double y = (double)foobar + x;
  printf("Value of y is %zu\n", (size_t)y);

  size_t size_of_foobar = sizeof(&foobar);
  printf("Size of address of foobar is %zu bytes\n", size_of_foobar);

  // NOLINTBEGIN(bugprone-sizeof-expression)
  printf("Size of pointer is %zu bytes\n", sizeof(another_name));
  // NOLINTEND(bugprone-sizeof-expression)

  printf("length of another_name is %zu bytes\n", strlen(another_name));

  size_t index = 0;
  if (another_name != NULL) {
    while (true) {
      if (another_name[index] == '\0') {
        break;
      }

      index += 1;
    }
  }

  printf("String: %s, Count: %zd, Manual Count: %zd\n", another_name,
         strlen(another_name), index);

  if (argc >= 2) {
    print_hello_world((size_t)argc, argv);
  }

  return 0;
}
