#include <stdio.h>

int main() {

    int intVar;
    char charVar;
    double doubleVar;
    short shortVar;

    printf("Size of int: %lu bytes\n", sizeof(intVar));
    printf("Size of char: %lu byte\n", sizeof(charVar));
    printf("Size of double: %lu bytes\n", sizeof(doubleVar));
    printf("Size of short: %lu bytes\n", sizeof(shortVar));

    printf("Address of intVar: %p\n", &intVar);
    printf("Address of charVar: %p\n", &charVar);
    printf("Address of doubleVar: %p\n", &doubleVar);
    printf("Address of shortVar: %p\n", &shortVar);

    return 0;
}
