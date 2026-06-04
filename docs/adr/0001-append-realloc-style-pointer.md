# ADR 0001: append_string_builder uses realloc-style pointer return

Date: 2026-06-04
Status: Accepted

## Context

`append_string_builder` may need to grow the underlying buffer. When it does,
the original allocation is freed and a new one is returned. The API must
communicate this to callers somehow.

Two shapes were considered:

**Option A — return new pointer (realloc-style)**

```c
s = append_string_builder(s, "more text");
```

Caller must reassign. Ignoring the return value after a reallocation leaves a
dangling pointer.

**Option B — double pointer (update in place)**

```c
append_string_builder(&s, "more text");
```

The function updates `*s` directly. Callers cannot accidentally ignore the
reallocation, but every call site carries the extra `&`.

## Decision

Use Option A (realloc-style return). The contract is documented in the header:
callers must always reassign from the return value.

## Rationale

- Mirrors the well-understood `realloc` contract that C programmers already know.
- Avoids double-pointer syntax at every call site, which adds visual noise with
  no correctness benefit when the convention is followed.
- Consistent with how existing C string-growth APIs (e.g. `SDL_RWops`, `stb_ds`)
  are shaped.

## Consequences

- Callers who ignore the return value silently get a dangling pointer. This
  risk is mitigated by documenting the contract in the header and naming the
  pattern explicitly in `CONTEXT.md`.
- A future static-analysis pass (e.g. clang-tidy `bugprone-unused-return-value`)
  can catch violations automatically.
