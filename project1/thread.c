#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_1(void *arg) {
    printf("thread_1 : 첫 번째 스레드...\n");
    pthread_exit(NULL);
}

void *thread_2(void *arg) {
    printf("thread_2 : 두 번째 스레드...\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t threadID1, threadID2;

    if(pthread_create(&threadID1, NULL, thread_1, NULL)) {
        fprintf(stderr, "생성 에러 : thread_1\n");
        return 1;
    }
    if(pthread_create(&threadID2, NULL, thread_2, NULL)) {
        fprintf(stderr, "생성 에러 : thread_2\n");
        return 2;
    }
    if(pthread_join(threadID1, NULL)) {
        fprintf(stderr, "종료 에러 : thread_1\n");
        return 3;
    }
    if(pthread_join(threadID2, NULL)) {
        fprintf(stderr, "종료 에러 : thread_2\n");
        return 4;
    }
    printf("메인 스레드 : 성공적으로 두 스레드 모두 종료함...\n");

    return 0;
}
