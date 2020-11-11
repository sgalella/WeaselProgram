CC = clang
LD = clang
CFLAGS = -g -Wall

.PHONY: all

all: main

main: bin/cumulative_selection

bin/cumulative_selection: src/cumulative_selection.c
	@mkdir -p bin/
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf bin