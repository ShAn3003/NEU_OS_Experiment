/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:16:32
 * @LastEditTime: 2024-05-19 16:16:32
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\mult_annoymous_pro_con.c
 */
/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:15:29
 * @LastEditTime: 2024-05-19 16:15:29
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\anonymous_mmap.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

void sys_error(const char *str) {
    perror(str);
    exit(1);
}

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} shared_memory;

void producer(shared_memory *shm, int id) {
    int item;
    while (1) {
        sleep(rand() % 3);
        item = rand() % 100;
        sem_wait(&shm->empty);
        sem_wait(&shm->mutex);

        shm->buffer[shm->in] = item;
        printf("Producer %d produced item %d at position %d\n", id, item, shm->in);
        shm->in = (shm->in + 1) % BUFFER_SIZE;

        sem_post(&shm->mutex);
        sem_post(&shm->full);
    }
}

void consumer(shared_memory *shm, int id) {
    int item;
    while (1) {
        sem_wait(&shm->full);
        sem_wait(&shm->mutex);

        item = shm->buffer[shm->out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, shm->out);
        shm->out = (shm->out + 1) % BUFFER_SIZE;

        sem_post(&shm->mutex);
        sem_post(&shm->empty);
        sleep(rand() % 3);
    }
}

int main(int argc, char *argv[]) {
    shared_memory *shm;
    shm = mmap(NULL, sizeof(shared_memory), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shm == MAP_FAILED) {
        sys_error("mmap error");
    }

    shm->in = 0;
    shm->out = 0;
    sem_init(&shm->empty, 1, BUFFER_SIZE);
    sem_init(&shm->full, 1, 0);
    sem_init(&shm->mutex, 1, 1);

    pid_t pid;
    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pid = fork();
        if (pid < 0) {
            sys_error("fork error");
        }
        if (pid == 0) {
            producer(shm, i);
            exit(0);
        }
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pid = fork();
        if (pid < 0) {
            sys_error("fork error");
        }
        if (pid == 0) {
            consumer(shm, i);
            exit(0);
        }
    }

    for (int i = 0; i < NUM_PRODUCERS + NUM_CONSUMERS; i++) {
        wait(NULL);
    }

    sem_destroy(&shm->empty);
    sem_destroy(&shm->full);
    sem_destroy(&shm->mutex);

    if (munmap(shm, sizeof(shared_memory)) == -1) {
        sys_error("munmap error");
    }

    return 0;
}
