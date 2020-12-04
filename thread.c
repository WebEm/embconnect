// C program to create a thread

// SPDX-License-Identifier: GPL-2.0+
/*

2020+ Copyright (c)
All rights reserved.
*/

#include<stdio.h>
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
