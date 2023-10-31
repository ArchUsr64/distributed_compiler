#include <stdio.h>
#include <stdlib.h>

#include "host.c"
#include "node.c"

int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("Invalid Usage\n");
		return EXIT_FAILURE;
	}
	if (argv[1][0] == 'h') {
		return run_host(argv[2]);
	}
	else {
		return run_node();
	}
	return EXIT_SUCCESS;
}
