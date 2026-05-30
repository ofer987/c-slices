---
name: fix-lint
description: Auto-fixes C source formatting by running clang-format in-place on every *.c and *.h file in the project root. Use when the user asks to fix lint, fix formatting, run clang-format, or auto-format C files.
---

# Fix Lint

## Steps

1. Run clang-format in-place on all project C files:

   ```bash
   bash .claude/skills/fix-lint/scripts/fix.sh
   ```

2. Show the user which files were changed (the script reports this).

3. Verify formatting is now clean:

   ```bash
   bash scripts/check-format.sh
   ```

## Rules

- Only format files in the project root (`*.c`, `*.h`). Never touch `vendor/`.
- If `check-format.sh` still reports failures after running the fix, report that to the user.
