/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:05:42
 * @LastEditTime: 2024-05-19 16:06:56
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\pthread_count_char.c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function(void *arg);
pthread_mutex_t work_mutex; /* 互斥量，保护工作区及额外变量time_to_exit */
#define WORK_SIZE 1024
char work_area[WORK_SIZE]; /* 工作区 */
int time_to_exit = 0;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    
    res = pthread_mutex_init(&work_mutex, NULL); /* 初始化互斥量 */
    if (res != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }
    
    res = pthread_create(&a_thread, NULL, thread_function, NULL); /* 创建新线程 */ 
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    /* 主线程 */
    printf("Input some text. Enter 'end' to finish\n");
    
    while (!time_to_exit) {
        pthread_mutex_lock(&work_mutex);
        fgets(work_area, WORK_SIZE, stdin);
        pthread_mutex_unlock(&work_mutex);
        
        if (strncmp(work_area, "end", 3) == 0) {
            pthread_mutex_lock(&work_mutex);
            time_to_exit = 1;
            pthread_mutex_unlock(&work_mutex);
        }
    }
    
    printf("\nWaiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    pthread_mutex_destroy(&work_mutex);
    exit(EXIT_SUCCESS);
}

/* 新线程 */
void *thread_function(void *arg) {
    while (!time_to_exit) {
        pthread_mutex_lock(&work_mutex);
        if (work_area[0] != '\0') {
            printf("You input %ld characters\n", strlen(work_area) - 1);
            work_area[0] = '\0'; /* 重置工作区 */
        }
        pthread_mutex_unlock(&work_mutex);
        sleep(1); /* 模拟处理时间 */
    }
    pthread_exit(0);
}
