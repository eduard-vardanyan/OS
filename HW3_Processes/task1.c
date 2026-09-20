#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    int ret = fork();

    if (ret == 0)
    {
        printf("Child PID: %d\n", getpid());
        exit(0);
    }
    else
    {
        printf("Parent PID: %d\n", getpid());
    }

    return 0;
}
