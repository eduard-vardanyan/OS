#include <stdio.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <stdlib.h>  

#define CHUNK 4096

int main() {
    char path1[256], path2[256];
    char buf1[CHUNK], buf2[CHUNK];
    int fd1, fd2;
    ssize_t n1, n2, nr, i, min;
    off_t offset = 0;   

    printf("Enter first file path: ");
    if (scanf("%255s", path1) != 1) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter second file path: ");
    if (scanf("%255s", path2) != 1) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }

    fd1 = open(path1, O_RDONLY);
    if (fd1 == -1) {
        perror("open first file failed");
        exit(EXIT_FAILURE);
    }
    fd2 = open(path2, O_RDONLY);
    if (fd2 == -1) {
        perror("open second file failed");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    while (1) {
        
        n1 = 0;
        while (n1 < CHUNK && (nr = read(fd1, buf1 + n1, CHUNK - n1)) > 0)
            n1 += nr;
        if (nr == -1) {
            perror("read first file failed");
            close(fd1);
            close(fd2);
            exit(EXIT_FAILURE);
        }

        n2 = 0;
        while (n2 < CHUNK && (nr = read(fd2, buf2 + n2, CHUNK - n2)) > 0)
            n2 += nr;
        if (nr == -1) {
            perror("read second file failed");
            close(fd1);
            close(fd2);
            exit(EXIT_FAILURE);
        }

        
        min = n1 < n2 ? n1 : n2;
        for (i = 0; i < min; i++) {
            if (buf1[i] != buf2[i]) {
                printf("Files differ at byte %ld\n", offset + i);
                close(fd1);
                close(fd2);
                exit(EXIT_FAILURE);
            }
        }

        
        if (n1 != n2) {
            printf("Files differ at byte %ld\n", offset + min);
            close(fd1);
            close(fd2);
            exit(EXIT_FAILURE);
        }

        if (n1 == 0)    
            break;

        offset += n1;
    }

    printf("Files are identical\n");

    close(fd1);
    close(fd2);
    return 0;
}
