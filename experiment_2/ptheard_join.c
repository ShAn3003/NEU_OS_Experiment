/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:02:39
 * @LastEditTime: 2024-05-19 16:02:39
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\ptheard_join.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
typedef struct thread_ret
{
    int var;
    char str[100];
} Th_Ret;

void sys_err(int ret,const char * str)
{
    fprintf(stderr,"%s%s\n",str,strerror(ret));
    exit(1);
}
void * tfn(void * arg)
{
    Th_Ret * tval;
    tval=malloc(sizeof(Th_Ret)); 
    tval->var=100;
    strcpy(tval->str,"thread return mesg");
    pthread_exit((void *)tval);
}
int main(int argc, char *argv[])
{
    pthread_t tid;
    Th_Ret * retval;
    int ret=pthread_create(&tid,NULL,tfn,NULL);
    if (ret !=0)
    {
        sys_err(ret,"pthread create error");
    }
    ret = pthread_join(tid,(void **)&retval);
     if (ret !=0)
    {
        sys_err(ret,"pthread join error");
    }
    printf("Thread return var : %d, mesg : %s\n",retval->var,retval->str);
    pthread_exit(NULL);
}
