/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:12:03
 * @LastEditTime: 2024-05-19 16:12:03
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\2_2.c
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 3  // 定义子进程数量

void sys_error(const char *str) {
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]) {
    int ret;
    int fd[2];
    char buf[1024];
    ret = pipe(fd);
    if (ret < 0) {
        sys_error("pipe create wrong");
    }

    for (int i = 0; i < NUM_CHILDREN; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            sys_error("fork wrong");
        } else if (pid == 0) {
            // 子进程
            close(fd[0]);  // 关闭读端 保证数据单向流动
            char child_msg[256];
            snprintf(child_msg, sizeof(child_msg), "child process %d sending message, pid: %d\n", i, getpid());
            write(fd[1], child_msg, strlen(child_msg));
            close(fd[1]);  // 关闭写端
            exit(0);  // 子进程退出
        }
    }

    // 父进程
    close(fd[1]);  // 关闭写端 保证数据单向流动
    while ((ret = read(fd[0], buf, sizeof(buf) - 1)) > 0) {
        buf[ret] = '\0';  // 确保字符串以null结尾
        printf("%s", buf);
    }
    if (ret < 0) {
        sys_error("read wrong");
    }
    close(fd[0]);

    // 等待所有子进程结束
    for (int i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    return 0;
}
