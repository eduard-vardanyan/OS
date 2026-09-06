#include <stdio.h>

int main() {
	int a=7;
	int *b = &a;
	int **c = &b;
	printf("Value of a: %d\n", a);
	printf("Value of a by b: %d\n", *b);
	printf("Value of a by c: %d\n", **c);
	return 0;
}
