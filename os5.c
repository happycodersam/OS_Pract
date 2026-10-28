#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[5], in = 0, out = 0, count = 0;
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        buffer[in] = i;
        in = (in + 1) % 5;
        count++;
        printf("Producer produced item %d. Items left in buffer: %d\n", i, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        out = (out + 1) % 5;
        count--;
        printf("Consumer consumed item %d. Items left in buffer: %d\n", item, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}