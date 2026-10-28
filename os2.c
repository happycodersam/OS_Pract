#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void sort(int a[], int n, int desc) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((desc && a[i] < a[j]) || (!desc && a[i] > a[j])) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
}

void print(int a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d\t", a[i]);
    printf("\n");
}

int main() {
    int a[10], n;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    printf("Enter integers: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    pid_t pid = fork();

    if (pid == 0) {
        sort(a, n, 0);
        printf("\nI am Child Process, my PID is %d\n", getpid());
        printf("Array in ascending order:\n");
        print(a, n);
    } else if (pid > 0) {
        wait(NULL);
        sort(a, n, 1);
        printf("\nI am Parent Process, my PID is %d\n", getpid());
        printf("Array in descending order:\n");
        print(a, n);
    } else {
        printf("Error in fork!\n");
    }

    return 0;
}