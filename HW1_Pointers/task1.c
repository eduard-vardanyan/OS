#include <stdio.h>

int main() {
	int a = 7;   //Declaring variable
    	int *b = &a; //Declaring pointer pointing to int above

    	printf("Value of a: %d\n", a); //Printing value of a
    	printf("Address of a (&a): %p\n", &a); //Addres of a using the a
    	printf("Address of a (via b): %p\n", b); //Address of a using *b

    	*b = 42; //Changing the value of a using *b
    	printf("New value of a: %d\n", a); //Printing value if a after modification

    return 0;
}
