
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void* example_thread_handler(void *arg);
struct node {
	int data;
};

struct node test;
int main(int argv, char *argc[])
{
	pthread_t thid;
	int ret;

	/*
	 * pthread_create is an api to create thread.
	 * Thread will have it's own stack and it's attributes
	 * Multiple Threads can be spawned inside a process and 
	 * can be easily communicated. Since all threads shares 
	 * the process address space inter threads communications
	 * are easy. Shared varaible access across threads can 
	 * be protected by mutex.
	 * Refer man page for more details.
	 * 
	 * Default stack size as per man page. However the stack size
	 * of the thread can be obtained using pthread_attr_getstacksize();
	 *
	 *      ┌─────────────┬────────────────────┐
         *      │Architecture │ Default stack size │
         *      ├─────────────┼────────────────────┤
         *      │i386         │               2 MB │
         *      ├─────────────┼────────────────────┤
         *      │IA-64        │              32 MB │
         *      ├─────────────┼────────────────────┤
         *      │PowerPC      │               4 MB │
         *      ├─────────────┼────────────────────┤
         *      │S/390        │               2 MB │
         *      ├─────────────┼────────────────────┤
         *      │Sparc-32     │               2 MB │
         *      ├─────────────┼────────────────────┤
         *      │Sparc-64     │               4 MB │
         *      ├─────────────┼────────────────────┤
         *      │x86_64       │               2 MB │
         *      └─────────────┴────────────────────┘
	 */
	test.data = 10;
	ret = pthread_create(&thid, NULL, example_thread_handler,
							(void*) &test);
	if (ret) {
		printf("Thread creation failed %d\n", ret);
		return -1;
	}
	
	printf("main process waiting for thread to exit\n");
	pthread_join(thid, NULL); //wait for thread handler to complete.
	printf("thread exited....\n");
}

static void * example_thread_handler(void *arg)
{
	int i = 20;
	struct node *tmp = (struct node *)arg;
	printf("In thread handler\n");
	while (i--) {
		if (tmp) {
			printf("data : %d\n", tmp->data++) ;
		}
		sleep(1);
	}
}
