---
name: c_strings-context
description: Domain glossary for the c_strings string manipulation library
---

# c_strings — Domain Glossary

## StringBuilder

An owning, growable character buffer. Holds a heap-allocated `char*` together
with a `length` (bytes currently in use, excluding the `\0` terminator) and a
`capacity` (maximum usable bytes before reallocation, also excluding the `\0`
terminator — the actual allocation is always `capacity + 1`). Automatically
reallocates when an append would exceed `capacity`, so callers never need to
call `strlen` to track used length.

**Not** a slice (which would be a non-owning view). **Not** a fixed-size buffer.

When an append would exceed `capacity`, the buffer is reallocated with
`new_capacity = new_length * 2`, where `new_length` is the length after the
append. This deliberately tracks the new content size, not the old capacity.

**Pointer stability:** `append_string_builder` may reallocate. Callers must
assign the return value to a new variable and check it for `NULL` before
discarding the original pointer. If the return value is `NULL`, the append
failed and the original `StringBuilder` remains valid and unchanged — continue
using it. Only replace the original pointer once a non-`NULL` result is
confirmed:

```c
struct StringBuilder* next = append_string_builder(s, "more");
if (next == nullptr) {
  // append failed; s is still valid
} else {
  s = next;
}
```

Ignoring the return value when a reallocation occurred leaves a dangling pointer.

Constructed with `make_string_builder`. Freed with `free_string_builder`.
