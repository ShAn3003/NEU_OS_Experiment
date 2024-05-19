/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:14:53
 * @LastEditTime: 2024-05-19 16:14:54
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\mmap_r.c
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
void sys_error(const char * str)
{
    perror(str);
    exit(1);
}
int main(int argc,char * argv[])
{
    char * p=NULL;
    int fd = open("testmap",O_RDONLY);
    if (fd <0)
    {
        sys_error("open wrong");
    }
    /*lseek extend file size and need I/O operation*/
    /*mmap need file size != 0*/
    // lseek(fd,10,SEEK_END);
    // write(fd,"\0",1);
    /*All operations above can be replaced by function truncate/ftruncate */

    p=mmap(NULL,50,PROT_READ,MAP_SHARED,fd,0);
    if (p==MAP_FAILED) //need check return value
    {
        sys_error("mmap error");
    }
    close(fd);

    while (1)
    {
        printf("get from mmap:%s",p);
        sleep(1);
    }
    
    int ret = munmap(p,50);
    if (ret==-1)
    {
        sys_error("munmap error");
    }
    
    return 0;
}
