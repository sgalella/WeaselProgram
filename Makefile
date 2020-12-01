CC = clang
LD = clang
CFLAGS = -Wall -Iinclude

vpath %.c src
vpath %.h include

.PHONY: all

all: main

main: bin/main bin/weasel_program
	$(LD) $(CFLAGS) $^ -o bin/$@

bin/main: main.c weasel_program.h
	@mkdir -p bin/
	$(CC) $(CFLAGS) -c $< -o $@

bin/weasel_program: weasel_program.c weasel_program.h
	@mkdir -p bin/
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf bin