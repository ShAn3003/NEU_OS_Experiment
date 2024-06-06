/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:59:14
 * @LastEditTime: 2024-05-19 15:59:14
 * @LastEditors: ShAn_3003
 * @Description:
 * @FilePath: \OS_Experiment\experiment_2\ptheard_create.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
int global_var = 100;
void *tfn(void *arg)
{
    printf("thread:pid = %d,tid =%lu\n", getpid(), pthread_self());
    global_var = 200;
    return NULL;
}
int main(int argc, char *argv[])
{
    pthread_t tid;
    tid = pthread_self();
    printf("main:pid = %d,tid =%lu\n", getpid(), tid);
    printf("Before create global_var:%d\n", global_var);
    int ret = pthread_create(&tid, NULL, tfn, NULL);
    if (ret != 0)
    {
        perror("pthread_create error");
    }
    // sleep(1); // main pthread wait before return
    printf("After create global_var:%d\n", global_var);
    // pthread_exit(NULL);
    return 0;
}
