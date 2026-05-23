CC = clang
WERROR ?= 1e
DEFAULT_CFLAGS = -x c -std=c23 -Wall -Wextra

ifeq ($(EXPERIMENTAL), 1)
	CFLAGS = $(DEFAULT_CFLAGS)
else
	CFLAGS = $(DEFAULT_CFLAGS) -Werror
endif

.PHONY: all
all: clean test build

build: main.c
	$(CC) $(CFLAGS) -o main main.c

run: all
	./main

.PHONY: test
test:

.PHONY: clean
clean:
	rm -f main
