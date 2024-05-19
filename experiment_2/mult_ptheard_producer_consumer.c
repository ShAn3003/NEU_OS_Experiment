/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:08:19
 * @LastEditTime: 2024-05-19 16:08:26
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\mult_ptheard_producer_consumer.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3

int buffer[NUM] = {0};
sem_t empty, product;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int i = 0;
    while (1) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        buffer[i] = rand() % 1000 + 1;
        printf("Producer %lu produce data: %d in position %d\n", pthread_self(), buffer[i], i);
        i = (i + 1) % NUM;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&product);
        
        sleep(rand() % 3);
    }
    
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int i = 0;
    while (1) {
        sem_wait(&product);
        pthread_mutex_lock(&mutex);
        
        printf("Consumer %lu consuming data: %d in position %d\n", pthread_self(), buffer[i], i);
        buffer[i] = 0;
        i = (i + 1) % NUM;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
        sleep(rand() % 3);
    }
    
    pthread_exit(NULL);
}

void sys_err(int ret, const char *str) {
    fprintf(stderr, "%s%s\n", str, strerror(ret));
    exit(1);
}

int main(int argc, char *argv[]) {
    pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
    srand(time(NULL));

    // Initialize semaphores
    sem_init(&empty, 0, NUM);
    sem_init(&product, 0, 0);
    
    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        int ret = pthread_create(&producers[i], NULL, producer, NULL);
        if (ret != 0) {
            sys_err(ret, "pthread create error:");
        }
    }

    // Create consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        int ret = pthread_create(&consumers[i], NULL, consumer, NULL);
        if (ret != 0) {
            sys_err(ret, "pthread create error:");
        }
    }

    // Join producer threads
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    // Join consumer threads
    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&product);
    pthread_mutex_destroy(&mutex);

    return 0;
}
