#!/usr/bin/env bash
set -euo pipefail

clang_format=$(which clang-format 2>/dev/null || echo /opt/homebrew/opt/llvm/bin/clang-format)

for file in *.c *.h; do
  [ -f "$file" ] || continue

  if ! diff -q "$file" <("$clang_format" "$file") > /dev/null 2>&1; then
    "$clang_format" -i "$file"
    echo "Fixed: $file"
  fi
done
