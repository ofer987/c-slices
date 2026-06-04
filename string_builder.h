#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct StringBuilder StringBuilder;

size_t
get_length(struct StringBuilder* s);

size_t
get_capacity(struct StringBuilder* s);

char*
get_value(struct StringBuilder* s);

bool
is_empty(struct StringBuilder* s);

// Returns nullptr if capacity == 0 or malloc fails.
struct StringBuilder*
make_string_builder(char* existing_value, size_t capacity);

void
free_string_builder(struct StringBuilder* s);

// Realloc-style: the original pointer may be freed on reallocation.
// Always reassign: s = append_string_builder(s, "more");
// Returns nullptr on allocation failure.
struct StringBuilder*
append_string_builder(struct StringBuilder* s, char* new_value);
