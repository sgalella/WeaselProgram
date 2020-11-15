CC = clang
LD = clang
CFLAGS = -g -Wall

.PHONY: all

all: main

main: bin/weasel_program

bin/weasel_program: src/weasel_program.c
	@mkdir -p bin/
	$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -rf bin