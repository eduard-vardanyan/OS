#include <stdio.h>
void swap(int *a, int *b); 
int main() {
	int i=5;
	int j=10;
	printf("Value of i %d, and values of j %d\n", i,  j);

	swap(&i,&j);
	printf("Valuess after swap i %d, j %d\n", i, j);
	return 0;
}
void swap(int *a, int *b){
	int tmp= *a;
	*a = *b;
	*b = tmp;
}

