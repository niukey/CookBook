//线程:验证两个线程同时运行
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void * thread_function(void *arg);
char msg[]="hello world";
int run_now = 1;    //线程运行标志：1，原始线程；2，新线程

int main(){
    
    int res;
    pthread_t a_thread;
    void *thread_rst;
    int print_cnt = 0; 

    //step1:创建线程
    res = pthread_create(&a_thread,NULL,thread_function,(void*)msg); //create!!!
    if(res != 0 )
    {
        perror("thread create failed");
        exit(EXIT_FAILURE);
    }
    //step2:同时运行验证
    while(print_cnt++<20)
    {
        if(1 == run_now)
        {
            printf("1");
            run_now = 2;
        }else
        {
            sleep(1);
        }
    }

    printf("\nwaiting for thread to finish...\n");
    res = pthread_join(a_thread,&thread_rst);
    if(res != 0 )
    {
        perror("thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("thread joined, it returned %s\n",(char*)thread_rst);
    printf("Message is now %s\n",msg);

    exit(EXIT_SUCCESS);

}
void * thread_function(void *arg)
{

    int print_cnt = 0; 
    //step2:同时运行验证
    while(print_cnt++<20)
    {
        if(2 == run_now)
        {
            printf("2");
            run_now = 1;
        }else
        {
            sleep(1);
        }
    }

    printf("\nthread_function is running ,Arg was %s\n",(char*)msg);
    sleep(1);
    strcpy(msg,"Bye!");
    pthread_exit("Thank you for the CPU time");
}
