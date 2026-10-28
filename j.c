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
    char text[SIZE], result[SIZE];
    int fd1, fd2, n, i;
    int chars = 0, words = 0, lines = 0, inWord = 0;
    FILE *fp;

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    fd1 = open(FIFO1, O_RDONLY);
    n = read(fd1, text, SIZE - 1);
    if (n < 0) n = 0;
    text[n] = '\0';
    close(fd1);

    for (i = 0; text[i] != '\0'; i++) {
        chars++;
        if (text[i] == '\n')
            lines++;
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
            inWord = 0;
        else if (!inWord) {
            inWord = 1;
            words++;
        }
    }

    fp = fopen("output.txt", "w");
    fprintf(fp, "Characters: %d\nWords: %d\nLines: %d\n", chars, words, lines);
    fclose(fp);

    fp = fopen("output.txt", "r");
    n = fread(result, 1, SIZE - 1, fp);
    result[n] = '\0';
    fclose(fp);

    fd2 = open(FIFO2, O_WRONLY);
    write(fd2, result, strlen(result) + 1);
    close(fd2);

    printf("Process 2: counted and sent results back to Process 1.\n");
    return 0;
}