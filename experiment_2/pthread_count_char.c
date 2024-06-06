/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:05:42
 * @LastEditTime: 2024-05-19 16:06:56
 * @LastEditors: ShAn_3003
 * @Description: Counts characters entered by the user and displays the count after "end" is entered.
 * @FilePath: \OS_Experiment\experiment_2\pthread_count_char.c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

void *thread_function(void *arg);
pthread_mutex_t work_mutex; /* Mutex to protect work area and time_to_exit */
#define WORK_SIZE 1024
char work_area[WORK_SIZE]; /* Work area to store user input */
int char_count = 0; // Variable to store the character count

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;

    res = pthread_mutex_init(&work_mutex, NULL); /* Initialize mutex */
    if (res != 0) {
        perror("Mutex initialization failed");
        exit(EXIT_FAILURE);
    }

    res = pthread_create(&a_thread, NULL, thread_function, NULL); /* Create new thread */
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    /* Main thread */
    printf("Input some text. Enter 'end' to finish\n");

    while (1) { // Loop indefinitely until "end" is entered
        pthread_mutex_lock(&work_mutex);
        fgets(work_area, WORK_SIZE, stdin);
        pthread_mutex_unlock(&work_mutex);

        if (strncmp(work_area, "end", 3) == 0) {
            break; // Exit the loop when "end" is entered
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

/* New thread */
void *thread_function(void *arg) {
    while (1) { // Loop indefinitely until the main thread exits
        pthread_mutex_lock(&work_mutex);
        if (work_area[0] != '\0') {
            char_count = strlen(work_area) - 1; // Calculate character count
            work_area[0] = '\0'; // Reset work area
            printf("You input %d characters\n", char_count);
        }
        pthread_mutex_unlock(&work_mutex);
        sleep(1); /* Simulate processing time */
    }
    pthread_exit(0);
}
