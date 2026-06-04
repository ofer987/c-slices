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

build: main.c string_builder.c
	mkdir -p dist
	$(CC) $(CFLAGS) -o dist/main main.c string_builder.c

run: all
	./dist/main

.PHONY: test
test: test_string_builder
	./test/test_string_builder

test_string_builder: test_string_builder.c string_builder.c vendor/unity/unity.c
	mkdir -p test
	$(CC) $(CFLAGS) -I. -o test/test_string_builder test_string_builder.c string_builder.c vendor/unity/unity.c

.PHONY: lint
lint:
	./scripts/check-format.sh

.PHONY: clean
clean:
	rm -rf ./dist/main ./test/test_string_builder
