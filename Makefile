CC = clang
CLANG_FORMAT := $(shell which clang-format 2>/dev/null || echo /opt/homebrew/opt/llvm/bin/clang-format)
WERROR ?= 1e
DEFAULT_CFLAGS = -x c -std=c23 -Wall -Wextra

ifeq ($(EXPERIMENTAL), 1)
	CFLAGS = $(DEFAULT_CFLAGS)
else
	CFLAGS = $(DEFAULT_CFLAGS) -Werror
endif

.PHONY: all
all: clean test build

build: main.c string_array.c
	$(CC) $(CFLAGS) -o main main.c string_array.c

run: all
	./main

.PHONY: test
test: test_string_array
	./test_string_array

test_string_array: test_string_array.c string_array.c vendor/unity/unity.c
	$(CC) $(CFLAGS) -I. -o test_string_array test_string_array.c string_array.c vendor/unity/unity.c

.PHONY: lint
lint:
	./scripts/check-format.sh

.PHONY: clean
clean:
	rm -f main test_string_array
