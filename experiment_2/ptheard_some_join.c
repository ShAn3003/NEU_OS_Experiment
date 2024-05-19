/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:04:25
 * @LastEditTime: 2024-05-19 16:04:32
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\ptheard_some_join.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// 线程函数
void* thread_function(void* arg) {
    int thread_num = *((int*)arg);  // 复制传入的线程编号
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("I am thread number %d, PID: %d, TID: %lu\n", thread_num, pid, (unsigned long)tid);
    free(arg);  // 释放分配的内存
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_threads>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    pthread_t threads[n];

    for (int i = 0; i < n; i++) {
        int* thread_num = malloc(sizeof(int));
        if (thread_num == NULL) {
            perror("Failed to allocate memory");
            exit(1);
        }
        *thread_num = i + 1;  // 保存当前线程编号

        // 创建线程
        if (pthread_create(&threads[i], NULL, thread_function, thread_num) != 0) {
            perror("Failed to create thread");
            free(thread_num);  // 释放内存
            exit(1);
        }
    }

    // 等待所有线程完成
    for (int i = 0; i < n; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }

    printf("All threads completed.\n");
    return 0;
}
