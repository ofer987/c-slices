#include "string_builder.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#define SB_REQUIRE(s, ret) \
  do {                     \
    if ((s) == nullptr) {  \
      return ret;          \
    }                      \
  } while (0)
#else
#define SB_REQUIRE(s, ret) assert((s) != nullptr)
#endif

struct StringBuilder {
  char* value;
  size_t length;
  size_t capacity;
};

size_t
get_length(struct StringBuilder* s) {
  SB_REQUIRE(s, 0);

  return s->length;
}

size_t
get_capacity(struct StringBuilder* s) {
  SB_REQUIRE(s, 0);

  return s->capacity;
}

char*
get_value(struct StringBuilder* s) {
  SB_REQUIRE(s, nullptr);

  return s->value;
}

bool
is_empty(struct StringBuilder* s) {
  SB_REQUIRE(s, true);

  return (bool)(s->length == 0);
}

void
free_string_builder(struct StringBuilder* s) {
  SB_REQUIRE(s, );

  free(s->value);
  free(s);
}

static struct StringBuilder*
add_capacity(struct StringBuilder* s, size_t new_capacity) {
  if (new_capacity <= s->capacity) {
    return nullptr;
  }

  struct StringBuilder* larger = make_string_builder(s->value, new_capacity);

  if (larger == nullptr) {
    return nullptr;
  }

  free_string_builder(s);

  return larger;
}

static struct StringBuilder*
write_at(size_t offset, char* src, struct StringBuilder* dest) {
  if (src == nullptr) {
    return dest;
  }

  size_t src_length = strlen(src);
  size_t new_length = offset + src_length;

  // Buffer overflow
  if (new_length < offset) {
    return nullptr;
  }

  // not enough capacity
  if (new_length > MAX_ARRAY_CAPACITY_SIZE) {
    return nullptr;
  }

  // Create new buffer
  if (new_length > dest->capacity) {
    // Can I double the capacity?
    size_t new_capacity = new_length * 2;

    // If there is not enough capacity, but still has enough leftover for the new_length
    if (new_capacity > MAX_ARRAY_CAPACITY_SIZE) {
      new_capacity = MAX_ARRAY_CAPACITY_SIZE;
    }

    dest = add_capacity(dest, new_capacity);

    if (dest == nullptr) {
      return nullptr;
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
    return nullptr;
  }

  // Validate that capacity is not larger than MAX_ARRAY_CAPACITY_SIZE and that it will not cause a
  // buffer overflow (e.g., wrap back to 0) if larger than the largest value of size_t
  if (capacity > MAX_ARRAY_CAPACITY_SIZE) {
    return nullptr;
  }

  struct StringBuilder* s = malloc(sizeof(struct StringBuilder));
  if (s == nullptr) {
    return nullptr;
  }

  // clang-format off
  *s = (struct StringBuilder) {
    .value = malloc(capacity + 1),
    .length = 0,
    .capacity = capacity
  };
  s->value[0] = '\0';
  // clang-format on

  if (s->value == nullptr) {
    free(s);

    return nullptr;
  }

  if (existing_value != nullptr) {
    struct StringBuilder* result = write_at(0, existing_value, s);
    if (result == nullptr) {
      free_string_builder(s);

      return nullptr;
    }

    s = result;
  }

  return s;
}

struct StringBuilder*
append_string_builder(struct StringBuilder* s, char* new_value) {
  SB_REQUIRE(s, nullptr);

  struct StringBuilder* result = write_at(s->length, new_value, s);

  if (result == nullptr) {
    return nullptr;
  }

  return result;
}
