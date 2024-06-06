/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:18:31
 * @LastEditTime: 2024-05-19 16:18:31
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_4\2_0.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_REQUESTS 20
#define PAGE_RANGE 20

// Function to generate a sequence of page requests
void generate_page_requests(int *page_requests) {
    for (int i = 0; i < PAGE_REQUESTS; i++) {
        page_requests[i] = rand() % PAGE_RANGE;
    }
}

// Function to find the least recently used page's index
int find_lru(int *pages, int *timestamps, int size) {
    int lru_index = 0;
    for (int i = 1; i < size; i++) {
        if (timestamps[i] < timestamps[lru_index]) {
            lru_index = i;
        }
    }
    return lru_index;
}

// LRU page replacement algorithm
int lru_algorithm(int *page_requests, int frame_count) {
    int frames[frame_count];
    int timestamps[frame_count];
    int time = 0;
    int page_faults = 0;
    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < PAGE_REQUESTS; i++) {
        int page = page_requests[i];
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                timestamps[j] = time++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int lru_index = find_lru(frames, timestamps, frame_count);
            frames[lru_index] = page;
            timestamps[lru_index] = time++;
            page_faults++;
        }
    }
    return page_faults;
}

// FIFO page replacement algorithm
int fifo_algorithm(int *page_requests, int frame_count) {
    int frames[frame_count];
    int fifo_index = 0;
    int page_faults = 0;
    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < PAGE_REQUESTS; i++) {
        int page = page_requests[i];
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[fifo_index] = page;
            fifo_index = (fifo_index + 1) % frame_count;
            page_faults++;
        }
    }
    return page_faults;
}

// Function to simulate and compare LRU and FIFO algorithms
void simulate_page_replacement() {
    int page_requests[PAGE_REQUESTS];
    generate_page_requests(page_requests);

    printf("Page Requests: ");
    for (int i = 0; i < PAGE_REQUESTS; i++) {
        printf("%d ", page_requests[i]);
    }
    printf("\n");

    // LRU algorithm with 5 frames
    int lru_faults_5 = lru_algorithm(page_requests, 5);
    printf("LRU with 5 frames: %d page faults\n", lru_faults_5);

    // LRU algorithm with 10 frames
    int lru_faults_10 = lru_algorithm(page_requests, 10);
    printf("LRU with 10 frames: %d page faults\n", lru_faults_10);

    // FIFO algorithm with 5 frames
    int fifo_faults_5 = fifo_algorithm(page_requests, 5);
    printf("FIFO with 5 frames: %d page faults\n", fifo_faults_5);

    // FIFO algorithm with 10 frames
    int fifo_faults_10 = fifo_algorithm(page_requests, 10);
    printf("FIFO with 10 frames: %d page faults\n", fifo_faults_10);
}

// Function to demonstrate Belady's anomaly with FIFO
void belady_anomaly_demo() {
    int page_requests[] = {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4};
    int length = sizeof(page_requests) / sizeof(page_requests[0]);

    int fifo_faults_3 = fifo_algorithm(page_requests, 3);
    int fifo_faults_4 = fifo_algorithm(page_requests, 4);

    printf("Belady's anomaly demonstration with sequence {0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4}:\n");
    printf("FIFO with 3 frames: %d page faults\n", fifo_faults_3);
    printf("FIFO with 4 frames: %d page faults\n", fifo_faults_4);
}

int main() {
    srand(time(NULL));

    simulate_page_replacement();
    belady_anomaly_demo();

    return 0;
}
