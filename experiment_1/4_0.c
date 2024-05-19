/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:33:53
 * @LastEditTime: 2024-05-19 15:35:25
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\4_0.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char str[10] = "Test str";

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
            printf("Child process #%d created, pid: %d, parent process pid: %d\n", i+1, getpid(), getppid());
            printf("Child process #%d: str address: %p, str value: %s\n", i+1, (void*)str, str);
            getchar();
            exit(0);  // 子进程立即退出，避免创建自己的子进程
        }
        else
        {
            // 父进程代码
            printf("Parent process pid: %d, created child process #%d with pid: %d\n", getpid(), i+1, pid);
            printf("Parent process: str address: %p, str value: %s\n", (void*)str, str);
            // 修改全局字符串
            snprintf(str, sizeof(str), "Parent%d", i+1);
            getchar();
        }
    }

    // 父进程等待所有子进程结束
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }

    printf("End of program\n");
    return 0;
}
