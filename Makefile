all:
	-mkdir bin
	gcc src/main.c -o bin/distributed_compiler

clean:
	@rm bin -r
