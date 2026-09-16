#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int ret1 = fork();

    if (ret1 == 0) {
        execl("/bin/ls", "ls", NULL);
    }
    else {
        wait(NULL);

        int ret2 = fork();

        if (ret2 == 0) {
            execl("/bin/date", "date", NULL);
        }
        else {
            wait(NULL);
            printf("Parent process done\n");
        }
    }

    return 0;
}
