/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:14:10
 * @LastEditTime: 2024-05-19 16:14:17
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\3_0.c
 */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

void sys_error(const char *str) {
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]) {
    int ret;
    int fd[2];
    
    ret = pipe(fd);
    if (ret < 0) {
        sys_error("pipe create wrong");
    }
    
    pid_t pid1 = fork();
    if (pid1 < 0) {
        sys_error("fork wrong");
    } else if (pid1 == 0) {
        // 子进程1：执行ls命令
        close(fd[0]);  // 关闭读端
        dup2(fd[1], STDOUT_FILENO);  // 将标准输出重定向到写端
        close(fd[1]);  // 关闭写端，因为dup2已经将fd[1]重定向到STDOUT_FILENO
        execlp("ls", "ls", NULL);
        sys_error("exec ls error");  // execlp返回值小于0说明执行失败
    }

    pid_t pid2 = fork();
    if (pid2 < 0) {
        sys_error("fork wrong");
    } else if (pid2 == 0) {
        // 子进程2：执行wc -l命令
        close(fd[1]);  // 关闭写端
        dup2(fd[0], STDIN_FILENO);  // 将标准输入重定向到读端
        close(fd[0]);  // 关闭读端，因为dup2已经将fd[0]重定向到STDIN_FILENO
        execlp("wc", "wc", "-l", NULL);
        sys_error("exec wc error");  // execlp返回值小于0说明执行失败
    }

    // 父进程：关闭管道两端并回收子进程
    close(fd[0]);  // 关闭读端
    close(fd[1]);  // 关闭写端
    waitpid(pid1, NULL, 0);  // 回收子进程1
    waitpid(pid2, NULL, 0);  // 回收子进程2
    
    return 0;
}
