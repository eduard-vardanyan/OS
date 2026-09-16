#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int ret = fork();

    if (ret == 0) {
        execl("/usr/bin/grep", "grep", "main", "task4.c", NULL);
    }
    else {
        wait(NULL);
        printf("Parent process completed\n");
    }

    return 0;
}
