
root_include_dir := include
root_source_dir  := src
compile_flags    := -Wall 
libs             := -lncurses
CC               := gcc

build:
	$(CC) -o bin/snake ${compile_flags} ${libs} ${root_source_dir}/*.c
debug_build: 
	$(CC) -o bin/snake -g ${compile_flags} ${libs} ${root_source_dir}/*.c
.PHONY: clean

clean:
	rm bin/snake
