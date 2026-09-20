#include <stdio.h>
#include <stdlib.h>

void function1(void)
{
    printf("Function 1 called\n");
}

void function2(void)
{
    printf("Function 2 called\n");
}

int main(void)
{
    atexit(function1);
    atexit(function2);


    printf("Before exit\n");

    exit(0);

    printf("After exit\n");

//    printf("Program is running\n");

    exit(0);
}
