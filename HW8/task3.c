#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>   
#include <stdlib.h>   

int main() {
    char path[256];
    char c;
    int fd;
    ssize_t nr;
    off_t size, pos;

    printf("Enter file path: ");
    if (scanf("%255s", path) != 1) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }
    
    fflush(stdout);

    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    for (pos = size - 1; pos >= 0; pos--) {
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("lseek failed");
            close(fd);
            exit(EXIT_FAILURE);
        }

        nr = read(fd, &c, 1);
        if (nr == -1) {
            perror("read failed");
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (nr == 0)    
            break;

        if (write(1, &c, 1) == -1) {    
            perror("write failed");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (write(1, "\n", 1) == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1)
        perror("close failed");

    return 0;
}
