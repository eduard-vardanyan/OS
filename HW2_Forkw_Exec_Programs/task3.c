#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int ret = fork();

    if (ret == 0) {
        execl("/bin/echo", "echo", "Hello from the child process", NULL);
    }
    else {
        wait(NULL);
        printf("Parent process done\n");
    }

    return 0;
}
