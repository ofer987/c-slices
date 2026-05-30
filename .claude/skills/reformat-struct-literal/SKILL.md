---
name: reformat-struct-literal
description: Reformats inline C compound literal struct assignments to multi-line style with clang-format off/on guards. Converts `*var = (struct T) { .a = x, .b = y };` to the expanded form with each field on its own line.
---

Find every compound literal struct assignment in the current file (or the file the user specifies) that matches this pattern — where the fields appear on the same line as the opening brace, or are aligned to the brace rather than indented:

```c
*var = (struct Type) { .field1 = value1,
                       .field2 = value2,
                       .field3 = value3 };
```

or the single-line form:

```c
*var = (struct Type) { .field1 = value1, .field2 = value2 };
```

Reformat each one to this style, preserving the indentation level of the `*var` line:

```c
// clang-format off
*var = (struct Type) {
  .field1 = value1,
  .field2 = value2,
  .field3 = value3
};
// clang-format on
```

Rules:

- The `// clang-format off` and `// clang-format on` lines get the same indentation as the `*var =` line.
- Each field is indented 2 spaces deeper than `*var =`.
- The closing `};` is at the same indentation as `*var =`.
- The last field has no trailing comma.
- If the block is already wrapped in `// clang-format off/on`, skip it.
- Do not change anything else in the file.

Read the file first, identify all matching blocks, then apply the edits.
