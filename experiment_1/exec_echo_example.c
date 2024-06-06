/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:41:29
 * @LastEditTime: 2024-05-19 15:41:37
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\execl\exec_echo_example.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Before exec\n");

    // 执行系统命令 echo
    if (execl("/bin/echo", "echo", "Hello from exec!", (char *)NULL) == -1) {
        perror("execl failed");
        exit(1);
    }

    // 由于 execl 替换了当前进程，这段代码不会被执行
    printf("This will not be printed\n");
    return 0;
}
