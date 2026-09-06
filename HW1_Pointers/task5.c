#include <stdio.h>

int main() {
	char str[] = "Hello";
	char  *p = &str[0];
	for(int i =0; i<sizeof(str); i++){
		printf("%c", *(p+i));
	}

	char *end =  p + (sizeof(str) - 1);
	int length = end - p;
	printf("\nLength: %d\n", length);
	return 0;
}
