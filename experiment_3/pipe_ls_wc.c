/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:13:01
 * @LastEditTime: 2024-05-19 16:13:20
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\pipe_ls_wc.c
 */
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
void sys_error(const char * str)
{
    perror(str);
    exit(1);
}
int main(int argc,char * argv[])
{
    int ret;
    int fd[2];
    char * str="parent process writing message\n";
    char buf[1024];
    ret=pipe(fd);
    if (ret < 0)
    {
        sys_error("pipe create wrong");
    }
    
    pid_t pid=fork();
    if (pid<0)
    {
        sys_error("fork wrong");
    }
    else if (pid==0)
    {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc","wc","-l",NULL);
        sys_error("exec error");
        // close(fd[0]); //If exec sucess , PC would not return here.
    }
    else if (pid>0)
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls",NULL);
		//wait(NULL)
        sys_error("exec error");
        // close(fd[1]);
    }
    return 0;
}
