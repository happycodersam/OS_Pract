#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        printf("CHILD PROCESS PID : %d\n", getpid());
        printf("PARENT PROCESS PPID : %d\n", getppid());
        exit(0);
    } else if (pid > 0) {
        sleep(2);
        printf("\n********ZOMBIE STATE********\n");
        // printf("UID   PID   PPID   C PRI NI ADDR SZ WCHAN TTY TIME CMD\n");
        char cmd[100];
        sprintf(cmd, " -p %d", pid);
        sprintf(cmd, "ps -o uid,pid,ppid,c,pri,ni,addr,sz,wchan,tty,time,cmd -p %d", pid);
        system(cmd);
        wait(NULL);
    } else {
        printf("Error in fork\n");
        return 1;
    }

    pid = fork();

    if (pid == 0) {
        sleep(2);
        printf("\n********ORPHAN STATE********\n");
        printf("CHILD PROCESS PID : %d\n", getpid());
        printf("PARENT PROCESS PPID : %d\n", getppid());
    } else if (pid > 0) {
        printf("TERMINATED CHILD PID : %d\n", pid);
        printf("PARENT PID (MAIN) : %d\n", getpid());
        printf("PARENTS PARENT PPID (BASH) : %d\n", getppid());
        exit(0);
    }

    return 0;
}
