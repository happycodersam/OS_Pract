#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int ch;
    printf("1. Zombie\n2. Orphan\nChoice: ");
    scanf("%d", &ch);

    pid_t pid = fork();

    if (pid < 0) return 1;

    if (ch == 1) {
        if (pid == 0) exit(0);
        printf("Parent: PID = %d, Child = %d\n", getpid(), pid);
        sleep(10);
        wait(NULL);
        printf("Zombie removed.\n");
    } else {
        if (pid == 0) {
            sleep(3);
            printf("Child: PID = %d, New Parent = %d\n",
                   getpid(), getppid());
        } else {
            printf("Parent exiting: PID = %d\n", getpid());
            exit(0);
        }
    }
    return 0;
}