#include "math.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a, b;
	printf("Enter first number: ");
	scanf("%d", &a);
	printf("Enter second number: ");
	scanf("%d", &b);
	printf("Sum: %d\n", add(a, b));
	return EXIT_SUCCESS;
}
