/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:05:12
 * @LastEditTime: 2024-05-19 16:05:12
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\ptheard_shared.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t mutex; // Define a mutex

void sys_err(int ret, const char *str) {
    fprintf(stderr, "%s%s\n", str, strerror(ret));
    exit(1);
}

void *tfn(void *arg) {
    srand(time(NULL));
    while (1) {
        pthread_mutex_lock(&mutex); // Lock the mutex before critical section
        printf("B-1 ");
        sleep(rand() % 3);
        printf("B-2\n");
        sleep(rand() % 3);
        pthread_mutex_unlock(&mutex); // Unlock the mutex after critical section
    }
}

int main(int argc, char *argv[]) {
    pthread_t tid;
    srand(time(NULL));

    int ret = pthread_mutex_init(&mutex, NULL);
    if (ret != 0) {
        sys_err(ret, "mutex init error");
        exit(1);
    }

    ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0) {
        sys_err(ret, "pthread create error");
    }

    // Detach the child thread to avoid resource leaks
    ret = pthread_detach(tid);
    if (ret != 0) {
        sys_err(ret, "pthread detach error");
    }

    while (1) {
        pthread_mutex_lock(&mutex); // Lock the mutex before critical section
        printf("A-1 ");
        sleep(rand() % 3);
        printf("A-2\n");
        sleep(rand() % 3);
        pthread_mutex_unlock(&mutex); // Unlock the mutex after critical section
    }

    // This line is unreachable due to the infinite loops in both threads.
    // However, it's included for completeness to show proper mutex destruction.
    ret = pthread_mutex_destroy(&mutex);
    if (ret != 0) {
        sys_err(ret, "mutex destroy error");
    }

    return 0; // This line is also unreachable, but included for completeness.
}
