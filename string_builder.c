#include "string_builder.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct StringBuilder {
  char* value;
  size_t length;
  size_t capacity;
};

size_t
get_length(struct StringBuilder* s) {
  return s->length;
}

size_t
get_capacity(struct StringBuilder* s) {
  return s->capacity;
}

char*
get_value(struct StringBuilder* s) {
  return s->value;
}

bool
is_empty(struct StringBuilder* s) {
  return (bool)(s->length == 0);
}

void
free_string_builder(struct StringBuilder* s) {
  free(s->value);

  free(s);
}

static struct StringBuilder*
add_capacity(struct StringBuilder* s, size_t new_capacity) {
  if (new_capacity <= s->capacity) {
    return NULL;
  }

  struct StringBuilder* larger = make_string_builder(s->value, new_capacity);

  free_string_builder(s);

  return larger;
}

static struct StringBuilder*
write_at(size_t offset, char* src, struct StringBuilder* dest) {
  if (src == NULL) {
    return dest;
  }

  size_t src_length = strlen(src);
  size_t new_length = offset + src_length;

  if (new_length > dest->capacity) {
    dest = add_capacity(dest, new_length * 2);

    if (dest == NULL) {
      return NULL;
    }
  }

  memcpy(dest->value + offset, src, src_length);
  dest->value[offset + src_length] = '\0';
  dest->length = new_length;

  return dest;
}

struct StringBuilder*
make_string_builder(char* existing_value, size_t capacity) {
  if (capacity == 0) {
    return NULL;
  }

  struct StringBuilder* s = malloc(sizeof(struct StringBuilder));
  if (s == NULL) {
    return NULL;
  }

  // clang-format off
  *s = (struct StringBuilder) {
    .value = malloc(capacity + 1),
    .length = 0,
    .capacity = capacity
  };
  // clang-format on

  if (s->value == NULL) {
    free(s);

    return NULL;
  }

  if (existing_value != NULL) {
    struct StringBuilder* result = write_at(0, existing_value, s);
    if (result == NULL) {
      free_string_builder(s);

      return NULL;
    }

    s = result;
  }

  return s;
}

struct StringBuilder*
append_string_builder(struct StringBuilder* s, char* new_value) {
  struct StringBuilder* result = write_at(s->length, new_value, s);

  if (result == NULL) {
    return NULL;
  }

  return result;
}
