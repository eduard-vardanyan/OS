#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int ret = fork();

    if (ret == 0)
    {
        printf("Child 1 PID: %d\n", getpid());
        exit(1);
    }
    else
    {
	int status1;
	wait(&status1);

        printf("Parent PID: %d\n", getpid());
       // wait(NULL);
	printf("Child 1 status: %d\n", status1);

        int ret2 = fork();

        if (ret2 == 0)
        {
          printf("Child 2 PID: %d\n", getpid());
          exit(2);
        }
        else
        {
	    int  status2;
	    waitpid(ret2, &status2, 0);
	    printf("Child 2 status: %d\n", status2);
//            waitpid(ret2, NULL, 0);
        }

    }

    return 0;
}
