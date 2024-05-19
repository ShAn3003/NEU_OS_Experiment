/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:19:49
 * @LastEditTime: 2024-05-19 16:19:49
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_4\1_0.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY_SIZE 1000
#define MIN_SIZE 10

// 定义空闲区结构体
typedef struct {
    int start;
    int end;
} FreeBlock;

// 定义已分配区结构体
typedef struct {
    char job_name[20];
    int start;
    int end;
} AllocatedBlock;

// 定义空闲区表和已分配区表
FreeBlock free_blocks[MAX_MEMORY_SIZE];
AllocatedBlock allocated_blocks[MAX_MEMORY_SIZE];

int free_blocks_count = 0;
int allocated_blocks_count = 0;

// 初始化
void initialize_memory() {
    free_blocks_count = 1;
    free_blocks[0].start = 0;
    free_blocks[0].end = MAX_MEMORY_SIZE - 1;
}

// 主存分配
void allocate_memory(char *job_name, int size) {
    int min_free_block_index = -1;
    int min_free_block_size = MAX_MEMORY_SIZE;

    // 查找最小空闲区
    for (int i = 0; i < free_blocks_count; i++) {
        int block_size = free_blocks[i].end - free_blocks[i].start + 1;
        if (block_size >= size && block_size < min_free_block_size) {
            min_free_block_index = i;
            min_free_block_size = block_size;
        }
    }

    if (min_free_block_index == -1) {
        printf("Error: No suitable free block found for allocation.\n");
        return;
    }

    // 分配空间
    AllocatedBlock allocated_block;
    strcpy(allocated_block.job_name, job_name);
    allocated_block.start = free_blocks[min_free_block_index].start;
    allocated_block.end = allocated_block.start + size - 1;

    // 更新空闲区表
    if (min_free_block_size - size <= MIN_SIZE) {
        // 不再分割空闲区
        free_blocks[min_free_block_index] = free_blocks[free_blocks_count - 1];
        free_blocks_count--;
    } else {
        free_blocks[min_free_block_index].start += size;
    }

    // 更新已分配区表
    allocated_blocks[allocated_blocks_count++] = allocated_block;

    printf("Memory allocated successfully for job: %s\n", job_name);
}

// 主存回收
void deallocate_memory(char *job_name) {
    int deallocated = 0;

    for (int i = 0; i < allocated_blocks_count; i++) {
        if (strcmp(allocated_blocks[i].job_name, job_name) == 0) {
            // 标记为释放
            FreeBlock free_block;
            free_block.start = allocated_blocks[i].start;
            free_block.end = allocated_blocks[i].end;
            free_blocks[free_blocks_count++] = free_block;

            // 从已分配区表中移除
            allocated_blocks[i] = allocated_blocks[allocated_blocks_count - 1];
            allocated_blocks_count--;

            deallocated = 1;
            break;
        }
    }

    if (!deallocated) {
        printf("Error: Job %s not found in allocated blocks.\n", job_name);
    } else {
        printf("Memory deallocated successfully for job: %s\n", job_name);
    }
}

// 打印空闲区表和已分配区表
void print_memory_status() {
    printf("Free Blocks:\n");
    for (int i = 0; i < free_blocks_count; i++) {
        printf("Start: %d, End: %d\n", free_blocks[i].start, free_blocks[i].end);
    }

    printf("\nAllocated Blocks:\n");
    for (int i = 0; i < allocated_blocks_count; i++) {
        printf("Job: %s, Start: %d, End: %d\n", allocated_blocks[i].job_name, allocated_blocks[i].start, allocated_blocks[i].end);
    }
}

int main() {
    initialize_memory();

    char job_name[20];
    int size;
    char option;

    while (1) {
        printf("\nOptions:\n");
        printf("1. Allocate Memory\n");
        printf("2. Deallocate Memory\n");
        printf("3. Print Memory Status\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf(" %c", &option);

        switch (option) {
            case '1':
                printf("Enter job name: ");
                scanf("%s", job_name);
                printf("Enter memory size needed: ");
                scanf("%d", &size);
                allocate_memory(job_name, size);
                break;
            case '2':
                printf("Enter job name to deallocate memory: ");
                scanf("%s", job_name);
                deallocate_memory(job_name);
                break;
            case '3':
                print_memory_status();
                break;
            case '4':
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid option!\n");
        }
    }

    return 0;
}
