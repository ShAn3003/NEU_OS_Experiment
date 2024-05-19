/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:05:12
 * @LastEditTime: 2024-05-19 16:05:12
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\ptheard_shared.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
pthread_mutex_t mutex; //define a mutex

void sys_err(int ret,const char *str)
{
    fprintf(stderr,"%s%s\n",str,strerror(ret));
    exit(1);
}
void *tfn(void * arg)
{
    srand(time(NULL));
    while (1)
    {
        printf("B-1 ");
        sleep(rand()%3);
        printf("B-2\n");
        sleep(rand()%3);
    }
    

}
int main(int argc, char *argv[])
{
    pthread_t tid;
    srand(time(NULL));
    int ret=pthread_mutex_init(&mutex,NULL);
    if (ret != 0 )
    {
       fprintf(stderr,"mutex init error %s\n",strerror(ret));
        exit(1);
    }
    
   ret= pthread_create(&tid,NULL,tfn,NULL);
   if (ret != 0 )
   {
       sys_err(ret,"pthread create error");
   }
    while (1)
    {
        printf("A-1 ");
        sleep(rand()%3);
        printf("A-2\n");
        sleep(rand()%3);
    }
    
    return 0;
}
