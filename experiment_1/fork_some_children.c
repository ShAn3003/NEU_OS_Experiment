/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:15:34
 * @LastEditTime: 2024-05-19 15:26:44
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\fork_some_children.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
int main(int argc, char *argv[])
{
    printf("before fork---\n");
    for (size_t i = 0; i < 3; i++)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            exit(1);
        }
        else if (pid == 0)
        {
            printf("child process is created,pid: %d"
                   ",parent process pid: %d\n",
                   getpid(), getppid());
            getchar();
        }
        else if (pid > 0)
        {
            printf("parent process pid: %d my parent process is %d \n", getpid(), getppid());
            getchar();
        }
    }
    printf("end of programe\n");
    return 0;
}
