#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1 PID: %d\n", getpid());
        exit(1);
    }

    int child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2 PID: %d\n", getpid());
        exit(2);
    }

    int status1;
    waitpid(child1, &status1, 0);

    printf("Child 1 exit status: %d\n", status1);

    if (WIFEXITED(status1))
    {
        printf("Child 1 exited normally\n");
    }
    else
    {
        printf("Child 1 exited with an error\n");
    }

    int status2;
    waitpid(child2, &status2, 0);

    printf("Child 2 exit status: %d\n", status2);

    if (WIFEXITED(status2))
    {
        printf("Child 2 exited normally\n");
    }
    else
    {
        printf("Child 2 exited with an error\n");
    }

    return 0;
}
