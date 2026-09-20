#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int ret = fork();

    if (ret == 0)
    {
        // Child
        printf("Child PID: %d\n", getpid());
        exit(0);
    }
    else
    {
        // Parent
        printf("Parent PID: %d\n", getpid());

        wait(NULL);
    }

    return 0;
}
