/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:15:29
 * @LastEditTime: 2024-05-19 16:15:29
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\anonymous_mmap.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/wait.h>
void sys_error(const char * str)
{
    perror(str);
    exit(1);
}

int main(int argc,char * argv[])
{
    char * p=NULL;
    // int fd = open("testmap",O_RDWR | O_CREAT | O_TRUNC,0644);
    // if (fd <0)
    // {
    //     sys_error("open wrong");
    // }
    /*lseek extend file size and need I/O operation*/
    /*mmap need file size != 0*/
    // lseek(fd,10,SEEK_END);
    // write(fd,"\0",1);
    /*All operations above can be replaced by function truncate/ftruncate */
    // ftruncate(fd,50);
    
    // int len=lseek(fd,0,SEEK_END);
    p=mmap(NULL,50,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANON,-1,0);
    if (p==MAP_FAILED) //need check return value
    {
        sys_error("mmap error");
    }

    pid_t pid;
    pid=fork();
    if (pid<0)
    {
        perror("fork error");
    }
    if (pid==0)
    {
        sleep(1);
        printf("child read mmap:%s\n",p);
    }
    else if(pid > 0)
    {
        strcpy(p,"mmap hello\n");
        wait(NULL);
        int ret = munmap(p,50);
        if (ret==-1)
        {
            sys_error("munmap error");
        }
    }

    return 0;
}
