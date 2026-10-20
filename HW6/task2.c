#include <stdio.h>

struct DataHolder1 {
    char a;
    int b;
    double c;
};

struct DataHolder2 {
    double c;
    int b;
    char a;
};

int main() {

    struct DataHolder1 example1;
    struct DataHolder2 example2;

    printf("Size of DataHolder1: %lu bytes\n", sizeof(struct DataHolder1));
    printf("Address of a: %p\n", &example1.a);
    printf("Address of b: %p\n", &example1.b);
    printf("Address of c: %p\n", &example1.c);

    printf("Size of DataHolder2: %lu bytes\n", sizeof(struct DataHolder2));
    printf("Address of c: %p\n", &example2.c);
    printf("Address of b: %p\n", &example2.b);
    printf("Address of a: %p\n", &example2.a);

    return 0;
}
