/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:36:47
 * @LastEditTime: 2024-05-19 15:36:54
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\execp_test.c
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
        // execlp("ls","-l","-h",NULL); wrong code
        execlp("ls","ls","-l","-h",NULL);
        perror("exec error");
        exit(1);
    }
    else if (pid > 0)
    {
        printf("parent process pid: %d my parent process is %d \n",getpid(),getppid());
        sleep(1);
    }
    return 0;
}

