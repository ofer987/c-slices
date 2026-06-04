#include "string_builder.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
print_hello_world(size_t count, char* names[]);

int
main(int argc, char* argv[]) {
  /* char *name = "Hello World"; */
  char* another_name = "Hello World";
  /* another_name[11] = 'a'; */

  size_t foobar = 123;

  double x = 0.23;
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

  printf("String: %s, Count: %zd, Manual Count: %zd\n", another_name, strlen(another_name), index);

  if (argc >= 2) {
    print_hello_world((size_t)argc, argv);
  }

  return 0;
}

void
print_hello_world(size_t count, char* names[]) {
  if (count < 2) {
    return;
  }

  struct StringBuilder* hello_world = make_string_builder("Hello", 20);

  if (count == 2) {
    hello_world = append_string_builder(hello_world, " ");
    hello_world = append_string_builder(hello_world, names[1]);
  } else if (count == 3) {
    hello_world = append_string_builder(hello_world, " ");
    hello_world = append_string_builder(hello_world, names[1]);
    hello_world = append_string_builder(hello_world, " and ");
    hello_world = append_string_builder(hello_world, names[2]);
  } else {
    for (size_t index = 1; index < count - 1; index += 1) {
      hello_world = append_string_builder(hello_world, " ");
      hello_world = append_string_builder(hello_world, names[index]);
      hello_world = append_string_builder(hello_world, ",");
    }

    hello_world = append_string_builder(hello_world, " and ");
    hello_world = append_string_builder(hello_world, names[count - 1]);
  }

  char* hello_world_value = get_value(hello_world);
  size_t hello_world_length = get_length(hello_world);
  size_t hello_world_capacity = get_capacity(hello_world);

  printf("Size of hello_world is %zu and strlen is %zu\n", hello_world_length, strlen(hello_world_value));
  printf("hello_world is \'%s\'\n", hello_world_value);
  printf("Capacity is %zu\n", hello_world_capacity);

  free_string_builder(hello_world);
}
