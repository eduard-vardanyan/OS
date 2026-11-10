#include <stdio.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <stdlib.h>  
#include <string.h>  

int main() {
    int fd;
    ssize_t nr;
    off_t size;

    fd = open("sparse.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        exit(EXIT_FAILURE);
    }

    nr = write(fd, "START", strlen("START"));
    if (nr == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    if (lseek(fd, 1024 * 1024, SEEK_CUR) == -1) {
        perror("lseek failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    nr = write(fd, "END", strlen("END"));
    if (nr == -1) {
        perror("write failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (close(fd) == -1) {
        perror("close failed");
        exit(EXIT_FAILURE);
    }

    fd = open("sparse.bin", O_RDONLY);
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
    printf("Apparent file size: %ld bytes\n", size);

    /*
     * Why du shows much less than the apparent size:
     * The 1 MiB gap was never written, so the file system does not
     * allocate disk blocks for it. It only records that this range is a
     * hole. Reading the hole returns zeros, but no zeros are stored on
     * disk. The apparent size (what lseek/ls -l report) is just the
     * offset of the last byte + 1. du counts only the blocks actually
     * allocated, which here are the block holding "START" and the block
     * holding "END" (for example 2 x 4 KiB = 8 KiB instead of ~1 MiB).
     */

    if (close(fd) == -1)
        perror("close failed");

    return 0;
}
