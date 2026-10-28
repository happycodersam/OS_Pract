#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define SIZE 1024

int main() {
    char text[SIZE] = "", line[256], result[SIZE];
    int fd1, fd2, n;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Enter sentences (type a single '.' on a new line to finish):\n");
    while (fgets(line, sizeof(line), stdin)) {
        if (strcmp(line, ".\n") == 0)
            break;
        if (strlen(text) + strlen(line) < SIZE - 1)
            strcat(text, line);
    }

    fd1 = open(FIFO1, O_WRONLY);
    write(fd1, text, strlen(text) + 1);
    close(fd1);

    fd2 = open(FIFO2, O_RDONLY);
    n = read(fd2, result, SIZE - 1);
    if (n < 0) n = 0;
    result[n] = '\0';
    close(fd2);

    printf("\n--- Result received from Process 2 ---\n%s", result);
    return 0;
}
