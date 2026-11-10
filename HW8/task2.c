#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char buffer[100];
    int fd;
    ssize_t nr;
    off_t size;

    
    fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    nr = write(fd, text, strlen(text));
    if (nr == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (nr != (ssize_t)strlen(text)) {
        printf("Partial write: %zd bytes\n", nr);
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1) {
        perror("close failed");
        exit(EXIT_FAILURE);
    }

    
    fd = open("data.txt", O_RDWR);
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
    printf("Size before truncate: %ld bytes\n", size);

    
    if (ftruncate(fd, 10) == -1) {
        perror("ftruncate failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Size after truncate: %ld bytes\n", size);

    
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    nr = read(fd, buffer, sizeof(buffer) - 1);
    if (nr == -1) {
        perror("read failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    buffer[nr] = '\0';
    printf("Content: %s\n", buffer);

    if (close(fd) == -1)
        perror("close failed");

    return 0;
}
