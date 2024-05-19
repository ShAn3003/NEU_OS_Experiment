/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 16:07:26
 * @LastEditTime: 2024-05-19 16:07:26
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\experiment_2\ptheard_producer_consumer.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#define NUM 5
int buffer[NUM]={0};
sem_t empty,product;

void * producer(void *arg)
{
    int i=0;
    while (1)
    {
        sem_wait(&empty);
        buffer[i]=rand()%1000+1;
        printf("Producer %lu produce data:%d in position %d\n",
            pthread_self(),buffer[i],i);
        i=(i+1)%NUM;
        sem_post(&product);
        sleep(rand()%3);
    }
    
    pthread_exit(NULL);
}
void * consumer(void *arg)
{
    int i=0;
    while (1)
    {
        sem_wait(&product);
        printf("Consumer %lu consuming data:%d in position %d\n",
            pthread_self(),buffer[i],i);
        buffer[i]=0;
        i++;
        i%=NUM;
        sem_post(&empty);
        sleep(rand()%3);
    }
    pthread_exit(NULL);
}

void sys_err(int ret,const char * str)
{
    fprintf(stderr,"%s%s\n",str,strerror(ret));
    exit(1);
}
int main(int argc, char *argv[])
{
    pthread_t ptid,ctid;
    srand(time(NULL));
    /*init sem*/
    sem_init(&empty,0,NUM);
    sem_init(&product,0,0);

    /*create produce consumer pthread*/
    int ret = pthread_create(&ptid,NULL,producer,NULL);
    if(ret != 0)
    {
        sys_err(ret,"pthread create error :");
    }
    pthread_create(&ctid,NULL,consumer,NULL);
    if(ret != 0)
    {
        sys_err(ret,"pthread create error :");
    }

    /*join pthread*/
    pthread_join(ptid,NULL);
    pthread_join(ctid,NULL);

    /*sem destroy*/
    sem_destroy(&empty);
    sem_destroy(&product);

    return 0;
}
