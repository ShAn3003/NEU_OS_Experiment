/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:09:15
 * @LastEditTime: 2024-05-19 16:09:22
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\dup.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
void sys_error(const char * str)
{
    perror(str);
    exit(1);
}
int main(int argc,char * argv[])
{
    int fd,newfd;
    char * teststr="/*test string */\n";
    fd=open(argv[1],O_RDWR);
    if (fd<0)
    {
        sys_error("open error");
    }
    printf("old fd %d\n",fd);
    newfd=dup(fd);
    printf("new fd %d\n",newfd);
write(newfd,teststr,strlen(teststr));
/*stdout redirect to file test*/
dup2(newfd,STDOUT_FILENO);
printf("test dup2 function \n");
close(fd);
close(newfd);
    return 0;
}
