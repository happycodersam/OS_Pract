
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;
int counter = 0;

void *fun(void *arg) {
    int id = *(int *)arg;

    sem_wait(&s);
    printf("Thread %d enters critical section\n", id);
    counter++;
    printf("Counter = %d\n", counter);
    printf("Thread %d leaves critical section\n", id);
    sem_post(&s);

    return NULL;
}

int main() {
    pthread_t t[3];
    int id[] = {1, 2, 3};

    sem_init(&s, 0, 1);

    for (int i = 0; i < 3; i++)
        pthread_create(&t[i], NULL, fun, &id[i]);

    for (int i = 0; i < 3; i++)
        pthread_join(t[i], NULL);

    sem_destroy(&s);
    return 0;
}
