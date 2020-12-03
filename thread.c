// C program to create a thread

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

void *thread_function()
{
        printf("Another thread is created\n");
        return NULL;
}

void main()
{
        pthread_t thread;
        printf("First thread is created\n");
        pthread_create(&thread, NULL, thread_function, NULL);
        pthread_join(thread, NULL);
}
