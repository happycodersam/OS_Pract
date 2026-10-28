
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char msg[100] = {0};
    mkfifo("myfifo", 0666);

    int fd = open("myfifo", O_RDONLY);
    int n = read(fd, msg, sizeof(msg) - 1);
    close(fd);

    if (n > 0)
        printf("Child received: %s\n", msg);

    return 0;
}
