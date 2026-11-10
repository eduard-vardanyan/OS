#include <stdio.h>
#include <fcntl.h>    
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buffer[256];
    char out[300];   
    int fd;
    ssize_t bytes_read, nr;
    int len, i;
    off_t pos;

    fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    
    write(1, "Enter a log line: ", strlen("Enter a log line: "));

    bytes_read = read(0, buffer, sizeof(buffer) - 1);    
    if (bytes_read == -1) {
        perror("read failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (bytes_read == 0) {    
        printf("No input\n");
        close(fd);
        return 0;
    }
    buffer[bytes_read] = '\0';

    
    for (i = 0; i < bytes_read; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            break;
        }
    }

    
    len = snprintf(out, sizeof(out), "PID=%d: %s\n", getpid(), buffer);

    nr = write(fd, out, len);
    if (nr == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (nr != len) {
        printf("Partial write: %zd of %d bytes\n", nr, len);
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    pos = lseek(fd, 0, SEEK_CUR);
    if (pos == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("New file offset: %ld\n", pos);

    if (close(fd) == -1)
        perror("close failed");

    return 0;
}
