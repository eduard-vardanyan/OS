#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char line[16];
    char c;
    char *rest;
    const char *new_line = "100\n";
    int fd, i, len, newlines;
    ssize_t nr;
    off_t pos, line4_start, line4_end, size, rest_len, done;

    
    fd = open("numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= 10; i++) {
        len = snprintf(line, sizeof(line), "%d\n", i);
        nr = write(fd, line, len);
        if (nr != len) {
            perror("write failed");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    if (close(fd) == -1) {
        perror("close failed");
        exit(EXIT_FAILURE);
    }

    
    fd = open("numbers.txt", O_RDWR);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    pos = 0;
    newlines = 0;
    line4_start = -1;
    line4_end = -1;
    while ((nr = read(fd, &c, 1)) == 1) {
        pos++;
        if (c == '\n') {
            newlines++;
            if (newlines == 3)
                line4_start = pos;  
            if (newlines == 4) {
                line4_end = pos;    
                break;
            }
        }
    }
    if (nr == -1) {
        perror("read failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (line4_end == -1) {
        printf("File has fewer than 4 lines\n");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Line 4 starts at offset %ld, next line at %ld\n", line4_start, line4_end);

   
    size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    rest_len = size - line4_end;

    rest = malloc(rest_len + 1);    
    if (rest == NULL) {
        perror("malloc failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (lseek(fd, line4_end, SEEK_SET) == -1) {
        perror("lseek failed");
        free(rest);
        close(fd);
        exit(EXIT_FAILURE);
    }

    done = 0;
    while (done < rest_len) {
        nr = read(fd, rest + done, rest_len - done);
        if (nr == -1) {
            perror("read failed");
            free(rest);
            close(fd);
            exit(EXIT_FAILURE);
        }
        if (nr == 0)
            break;
        done += nr;
    }
    rest_len = done;

   
    if (lseek(fd, line4_start, SEEK_SET) == -1) {
        perror("lseek failed");
        free(rest);
        close(fd);
        exit(EXIT_FAILURE);
    }

    nr = write(fd, new_line, strlen(new_line));
    if (nr != (ssize_t)strlen(new_line)) {
        perror("write failed");
        free(rest);
        close(fd);
        exit(EXIT_FAILURE);
    }

    nr = write(fd, rest, rest_len);
    if (nr != rest_len) {
        perror("write failed");
        free(rest);
        close(fd);
        exit(EXIT_FAILURE);
    }
    free(rest);

       if (ftruncate(fd, line4_start + strlen(new_line) + rest_len) == -1) {
        perror("ftruncate failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

        if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    fflush(stdout);
    while ((nr = read(fd, &c, 1)) == 1)
        write(1, &c, 1);
    if (nr == -1)
        perror("read failed");

    if (close(fd) == -1)
        perror("close failed");

    return 0;
}
