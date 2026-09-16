#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int ret1 = fork();

    if (ret1 == 0) {
        printf("Parent 1: PID:%d PPID:%d\n", getpid(), getppid());

        int ret11 = fork();

        if (ret11 == 0) {
            printf("Child 1.1: PID:%d PPID:%d\n", getpid(), getppid());

            int ret111 = fork();

            if (ret111 == 0)
                printf("Child 1.1.1: PID:%d PPID:%d\n", getpid(), getppid());
            else {
                int ret112 = fork();

                if (ret112 == 0)
                    printf("Child 1.1.2: PID:%d PPID:%d\n", getpid(), getppid());
                else {
                    wait(NULL);
                    wait(NULL);
                }
            }
        }
        else
            wait(NULL);
    }
    else {
        int ret2 = fork();

        if (ret2 == 0) {
            printf("Parent 2: PID:%d PPID:%d\n", getpid(), getppid());

            int ret21 = fork();

            if (ret21 == 0) {
                printf("Child 2.1: PID:%d PPID:%d\n", getpid(), getppid());

                int ret211 = fork();

                if (ret211 == 0)
                    printf("Child 2.1.1: PID:%d PPID:%d\n", getpid(), getppid());
                else {
                    int ret212 = fork();

                    if (ret212 == 0)
                        printf("Child 2.1.2: PID:%d PPID:%d\n", getpid(), getppid());
                    else {
                        wait(NULL);
                        wait(NULL);
                    }
                }
            }
            else
                wait(NULL);
        }
        else {
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
