#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX 5
#define BUF_S 1024

char messagebuf[BUF_S];
int messageAA = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t messageCond = PTHREAD_COND_INITIALIZER;

void *serverThread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        while (!messageAA) {
            pthread_cond_wait(&messageCond, &mutex);
        }
        printf(" 서버 : %s\n", messagebuf);
        messageAA = 0; 
        pthread_cond_broadcast(&messageCond);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *clientThread(void *arg) {
    int clientId = *((int*)arg);
    char tempBuffer[BUF_S];

    while (1) {
        snprintf(tempBuffer, BUF_S, " 클라이언트 [%d]", clientId);
        pthread_mutex_lock(&mutex);
        while (messageAA) {
            pthread_cond_wait(&messageCond, &mutex);
        }
        strcpy(messagebuf, tempBuffer);
        messageAA = 1;
        pthread_cond_signal(&messageCond);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t server, clients[MAX];
    int clientIds[MAX];
    pthread_create(&server, NULL, serverThread, NULL);
    for (int i = 0; i < MAX; i++) {
        clientIds[i] = i;
        pthread_create(&clients[i], NULL, clientThread, (void*)&clientIds[i]);
    }
    pthread_join(server, NULL);
    for (int i = 0; i < MAX; i++) {
        pthread_join(clients[i], NULL);
    }
    return 0;
}
