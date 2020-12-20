// C program to create a thread

// SPDX-License-Identifier: GPL-2.0+
/*

2020+ Copyright (c) gayathri-bytes <gaya3velu.25@gmail.com>
All rights reserved.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function()
{
        printf("Another thread is created\n");
        return NULL;
}

void main()
{
        int return;
        pthread_t thread;
        printf("First thread is created\n");
        return = pthread_create(&thread, NULL, thread_function, NULL);
        if (return != 0 )
                printf("Thread couldn't be created %d", return);
        pthread_join(thread, NULL);
}
