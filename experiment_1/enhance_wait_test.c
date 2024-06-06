/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:44:16
 * @LastEditTime: 2024-05-19 15:44:16
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\wait_test.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("before fork---\n");

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("child process is created, pid: %d, parent process pid: %d\n", getpid(), getppid());
        sleep(10); // Sleep for 10 seconds
        return 3;
    } else if (pid > 0) {
        printf("parent process pid: %d my parent process is %d \n", getpid(), getppid());

        int status;
        pid_t wpid = wait(&status);
        if (wpid == -1) {
            perror("wait error");
            exit(1);
        }

        if (WIFEXITED(status)) { // Check if child exited normally
            printf("child exit with status: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) { // Check if child was terminated by a signal
            printf("child was terminated by signal: %d\n", WTERMSIG(status));
        } else {
            printf("Unknown child process termination status\n");
        }
    }

    printf("end of program\n");
    return 0;
}
