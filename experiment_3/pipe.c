/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:10:55
 * @LastEditTime: 2024-05-19 16:10:55
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_3\pipe.c
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
        close(fd[1]); //关闭写端 保证数据单向流动
        ret=read(fd[0],buf,sizeof(buf));
        if (ret <= 0)
        {
            sys_error("read wrong");
        }
		printf("read ret %d\n",ret);
        printf("%s",buf);
        close(fd[0]);
    }
    else if (pid>0)
    {
        close(fd[0]); //关闭读端 保证数据单向流动
        // sleep(10);
        write(fd[1],str,strlen(str));
        
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
