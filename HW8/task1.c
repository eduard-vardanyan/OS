#include <stdio.h>
#include <fcntl.h>
#include <unistd.h> 
#include <stdlib.h> 

int main() {
    char src_path[256];
    char dst_path[256];
    char buffer[1024];
    int src_fd, dst_fd;
    ssize_t bytesRead, bytesWritten;
    ssize_t total = 0;

     
    printf("Enter source file path: ");
    if (scanf("%255s", src_path) != 1) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }
    printf("Enter destination file path: ");
    if (scanf("%255s", dst_path) != 1) {
        printf("Invalid input\n");
        exit(EXIT_FAILURE);
    }

    
    src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("open source failed");
        exit(EXIT_FAILURE);
    }

    
    dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        perror("open destination failed");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    
    while ((bytesRead = read(src_fd, buffer, sizeof(buffer))) > 0) {
        
        ssize_t done = 0;
        while (done < bytesRead) {
            bytesWritten = write(dst_fd, buffer + done, bytesRead - done);
            if (bytesWritten == -1) {
                perror("write failed");
                close(src_fd);
                close(dst_fd);
                exit(EXIT_FAILURE);
            }
            done += bytesWritten;
        }
        total += done;
    }

    if (bytesRead == -1) {
        perror("read failed");
        close(src_fd);
        close(dst_fd);
        exit(EXIT_FAILURE);
    }

    if (close(src_fd) == -1)
        perror("close source failed");
    if (close(dst_fd) == -1)
        perror("close destination failed");

    printf("Copied %zd bytes\n", total);
    return 0;
}
