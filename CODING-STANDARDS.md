# Coding Standards

## Language and toolchain

- C23 (`-std=c23`) compiled with `clang`
- Flags: `-Wall -Wextra -Werror` (all warnings are errors)
- Formatting enforced by `clang-format` (see `.clang-format`)
- LSP via `clangd` (see `.clangd`)

## Formatting

Run `clang-format` before committing. Key rules from `.clang-format`:

- 2-space indent
- 120-column limit
- Pointer alignment: left — `char* p`, not `char *p`
- Return type on its own line:

  ```c
  char*
  get_value(struct ArraySlice* s);
  ```

- Always use braces for control statements (`InsertBraces: true`)
- No short `if`/`for`/`while` on a single line
- Sort `#include` directives; project headers before system headers
- Always place a blank line before a `return` statement:

  ```c
  size_t length = compute_length(s);

  return length;
  ```

- Always place a blank line before a `free` or a `free_*` statement:

  ```c

  char* buf = malloc(40);

  free(buf);
  ```

  And,

  ```c
  char* bug = make_memory(40);

  free_memory(buf);
  ```

  However, multiple `free` and `free_*` statements can be placed together without line breaks, e.g.,

  ```c
  int index = 1;

  free_memory(buf);
  free_memory(result);
  free(c);
  ```

- Always place a blank line after a guard clause (an early `return` that exits on invalid input):

  ```c
  if (capacity == 0) {
    return NULL;
  }

  char* buf = malloc(capacity);
  ```

## Naming

- `snake_case` for functions, variables, and struct fields
- Constructors: `make_<type>` (e.g. `make_string_array`)
- Destructors: `free_<type>` (e.g. `free_string_array`, `free_result`)
- Getters: `get_<field>` (e.g. `get_length`, `get_value`)
- Boolean getters: `is_<state>` (e.g. `is_empty`, `is_success`)

## Opaque struct pattern

Struct definitions live in `.c` files. Headers expose only `typedef` declarations and function signatures — callers never touch fields directly.

```c
// string_array.h
typedef struct ArraySlice ArraySlice;
size_t get_length(struct ArraySlice* s);

// string_array.c
struct ArraySlice {
  char* value;
  size_t length;
  size_t capacity;
  bool is_empty;
};
```

## Memory management

- Every allocated type has a matching `free_*` function; always call it when done.
- Constructors (`make_*`) return `NULL` on failure — check before use.
- The caller owns any pointer returned by a constructor or getter and is responsible for freeing it.
- Do not access struct fields directly; use the provided getters.

## Error handling

Use the `Result` type to return success or failure from operations that can fail:

```c
struct Result* r = copy_into_array_slice(0, value, s);
if (!is_success(r)) {
  // handle error via get_error_message(r)
}

free_result(r);
```

Always `free_result` after inspecting the result, even on the success path.

## Compound literal struct assignments

Compound literal assignments must be written in expanded multi-line form and wrapped with `// clang-format off/on` guards so clang-format does not collapse them:

```c
// clang-format off
*result = (struct Result) {
  .array_slice = destination,
  .error_message = NULL,
  .is_success = true
};
// clang-format on
```

- Fields indented 2 spaces deeper than the assignment line.
- Closing `};` at the same indent as the assignment.
- No trailing comma on the last field.

## Git commit messages

Follow the [Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/) specification.

**Format:**

```gitcommit
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

**Types:**

| Type       | When to use                                      |
| ---------- | ------------------------------------------------ |
| `feat`     | New feature (MINOR version bump)                 |
| `fix`      | Bug fix (PATCH version bump)                     |
| `build`    | Build system or external dependency changes      |
| `chore`    | Maintenance tasks that don't modify src or tests |
| `ci`       | CI configuration changes                         |
| `docs`     | Documentation only                               |
| `style`    | Formatting, whitespace — no logic change         |
| `refactor` | Code restructure without feature or fix          |
| `perf`     | Performance improvement                          |
| `test`     | Adding or correcting tests                       |
| `revert`   | Reverts a previous commit                        |

**Breaking changes** — use `!` before the colon or a `BREAKING CHANGE:` footer:

```gitcommit
feat!: remove deprecated append API

BREAKING CHANGE: append_string_array no longer accepts NULL array_slice.
```

**Rules:**

- First line (`type[scope]: description`) must be 72 characters or fewer
- Description is lowercase, imperative mood, no trailing period
- Body begins one blank line after the description; each line 72 characters or fewer
- Footers begin one blank line after the body, using `Token: value` syntax (hyphens instead of spaces in token names)

## Testing

- Framework: Unity (vendored in `vendor/unity/`)
- One test function per observable behavior; name as `test_<function>_<condition>`
- Run with `make test`; tests must pass before merging
