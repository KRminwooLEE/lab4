#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BF_S 5
int buffer[BF_S];
int count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    int produced = 0;
    while (produced < 10) {
        pthread_mutex_lock(&mutex);
        if (count < BF_S) {
            buffer[count] = rand() % 100;
            printf("Pd %d produce: %d, Buffer: [", *((int*)arg), buffer[count]);
            for(int i = 0; i <= count; i++) {
                printf("%d ", buffer[i]);
            }
            printf("]\n");
            count++;
            produced++;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int consumed = 0;
    while (consumed < 10) {
        pthread_mutex_lock(&mutex);
        if (count > 0) {
            count--;
            printf("Cs %d consume: %d, Buffer: [", *((int*)arg), buffer[count]);
            for(int i = 0; i < count; i++) {
                printf("%d ", buffer[i]);
            }
            printf("]\n");
            consumed++;
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t p1, p2, c1, c2;
    int ids[4] = {1, 2, 1, 2};

    pthread_create(&p1, NULL, producer, (void*)&ids[0]);
    pthread_create(&p2, NULL, producer, (void*)&ids[1]);

    pthread_create(&c1, NULL, consumer, (void*)&ids[2]);
    pthread_create(&c2, NULL, consumer, (void*)&ids[3]);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(c1, NULL);
    pthread_join(c2, NULL);

    return 0;
}
