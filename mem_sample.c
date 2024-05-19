/*
 * @Author: ShAn_3003
 * @Date: 2024-05-19 15:45:13
 * @LastEditTime: 2024-05-19 15:45:13
 * @LastEditors: ShAn_3003
 * @Description: 
 * @FilePath: \OS_Experiment\mem_sample.c
 */
#include<stdlib.h>
#include <stdio.h>
#include <unistd.h>
int global_val = 10;
int uinit_global_val;
int add(int a,int b)
{
	return a+b;
}
int main(void)
{
    int a;
    static int static_val = 20;
    static int uinit_local_val;
    a = add(2,3);
    int * p = (int *)malloc(100);
    printf("a= %d\n",a);
    /*
    * 添加代码 打印global_val、a、staticl_val、p的地址
    */
   free(p);
   sleep(1000);
    return 0;
}

