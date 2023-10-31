all:
	-mkdir bin
	gcc src/main.c -o bin/distributed_compiler

clean:
	-@rm bin -r
	-@rm *.o
	-@rm *.out
	-@rm out.c

example: all
	./bin/distributed_compiler host example/main.c
	@echo "Sent main.c to node for compilation"
	@sleep 1
	@gcc example/math.c -c
	@gcc out.o math.o
	@echo "Successfully created final executable"
