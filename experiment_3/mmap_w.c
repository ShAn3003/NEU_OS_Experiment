/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:14:35
 * @LastEditTime: 2024-05-19 16:14:43
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\mmap_w.c
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
    char buf[50]={0};
    int fd = open("testmap",O_RDWR | O_CREAT | O_TRUNC,0644);
    if (fd <0)
    {
        sys_error("open wrong");
    }
    /*lseek extend file size and need I/O operation*/
    /*mmap need file size != 0*/
    // lseek(fd,10,SEEK_END);
    // write(fd,"\0",1);
    /*All operations above can be replaced by function truncate/ftruncate */
    ftruncate(fd,50);
    
    int len=lseek(fd,0,SEEK_END);
    p=mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (p==MAP_FAILED) //need check return value
    {
        sys_error("mmap error");
    }
    close(fd);
    int i=0;
    while (1)
    {
        sprintf(p,"%d, process 1 writing message\n",i++);
        sleep(1);
    }
    
    int ret = munmap(p,len);
    if (ret==-1)
    {
        sys_error("munmap error");
    }
    
    return 0;
}
