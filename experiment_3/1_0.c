/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:10:11
 * @LastEditTime: 2024-05-19 16:10:18
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\1_0.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

void sys_error(const char *str) {
    perror(str);
    exit(1);
}

int main(int argc, char *argv[]) {
    int fd, newfd;
    char *teststr = "/*test string */\n";
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        sys_error("open error");
    }

    printf("old fd %d\n", fd);
    newfd = dup(fd);
    printf("new fd %d\n", newfd);
    
    write(newfd, teststr, strlen(teststr));

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        sys_error("fork error");
    } else if (pid == 0) {
        // Child process: redirect stdout to file
        if (dup2(newfd, STDOUT_FILENO) < 0) {
            sys_error("dup2 error");
        }
        close(fd);
        close(newfd);

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        sys_error("execlp error");  // execlp only returns on error
    } else {
        // Parent process: wait for the child to finish
        wait(NULL);
    }

    close(fd);
    close(newfd);
    
    return 0;
}
