/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:43:30
 * @LastEditTime: 2024-05-19 15:43:36
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\zombie.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
int main(int argc, char *argv[])
{
    printf("before fork---\n");
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("child process is created,pid: %d"
        ",parent process pid: %d\n",getpid(),getppid());
       sleep(10);
        
    }
    else if (pid > 0)
    {
        printf("parent process pid: %d my parent process is %d \n",getpid(),getppid());
         while (1)
        {
            printf("parent process is running . ppid: %d\n",getpid());
            sleep(1);
        }
    }
    printf("end of programe\n");
    return 0;
}
