/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:44:49
 * @LastEditTime: 2024-05-19 15:44:55
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\waitpid_test.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    pid_t pid,tmpid,wpid;
    int i;
    printf("before fork---\n");
    for (i = 0; i < 10; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork error");
            exit(1);
        }
      
        
        if (pid == 0)
        {
            break;
        }
          if (i== 2)
        {
            tmpid=pid;
            printf("child process %d to be waited\n",tmpid);
        }
    }
    if (pid == 0)
    {
        printf("child process is created,pid: %d"
               ",parent process pid: %d"
               ",I'm num %d\n",
               getpid(), getppid(),i);
    }
    else if (pid > 0)
    {
        printf("parent process pid: %d my parent process is %d \n", getpid(), getppid());
        wpid=waitpid(tmpid,NULL,0) ;//wait a child process. blocked
        if (wpid == -1)
        {
            perror("waitpid error");
            exit(1);
        }
        printf("parent process wait child %d\n",wpid);
        
    }

    // printf("end of programe\n");
    return 0;
}
