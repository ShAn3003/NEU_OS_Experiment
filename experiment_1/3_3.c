/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:15:34
 * @LastEditTime: 2024-05-19 15:31:34
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\3_3.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_children>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    printf("before fork---\n");

    for (int i = 0; i < n; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0)
        {
            // 子进程代码
            sleep(1); // 暂停 1 秒，确保父进程先执行
            printf("Child process #%d created, pid: %d, parent process pid: %d\n", i+1, getpid(), getppid());
            exit(0);  // 子进程立即退出，避免创建自己的子进程
        }
        else
        {
            // 父进程代码
            printf("Parent process pid: %d, created child process #%d with pid: %d\n", getpid(), i+1, pid);
            sleep(1); // 暂停 1 秒，确保子进程有机会执行
        }
    }

    // 父进程等待所有子进程结束
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("End of program\n");
    return 0;
}
