#include <stdio.h>

struct NormalStruct {
    char a;
    int b;
    double c;
};

#pragma pack(1)
struct PackedStruct {
    char a;
    int b;
    double c;
};
#pragma pack()

#pragma pack(2)
struct PackedStruct2 {
    char a;
    int b;
    double c;
};
#pragma pack()

#pragma pack(4)
struct PackedStruct4 {
    char a;
    int b;
    double c;
};
#pragma pack()

int main() {

    struct NormalStruct example;
    struct PackedStruct example1;
    struct PackedStruct2 example2;
    struct PackedStruct4 example4;

    printf("Size of NormalStruct: %lu bytes\n", sizeof(struct NormalStruct));
    printf("Address of a: %p\n", &example.a);
    printf("Address of b: %p\n", &example.b);
    printf("Address of c: %p\n", &example.c);

    printf("Size of PackedStruct: %lu bytes\n", sizeof(struct PackedStruct));
    printf("Address of a: %p\n", &example1.a);
    printf("Address of b: %p\n", &example1.b);
    printf("Address of c: %p\n", &example1.c);

    printf("Size of PackedStruct2: %lu bytes\n", sizeof(struct PackedStruct2));
    printf("Address of a: %p\n", &example2.a);
    printf("Address of b: %p\n", &example2.b);
    printf("Address of c: %p\n", &example2.c);

    printf("Size of PackedStruct4: %lu bytes\n", sizeof(struct PackedStruct4));
    printf("Address of a: %p\n", &example4.a);
    printf("Address of b: %p\n", &example4.b);
    printf("Address of c: %p\n", &example4.c);

    return 0;
}
