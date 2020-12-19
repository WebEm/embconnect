
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int shared_variable = 0;
pthread_mutex_t var_mutex;

/*
 * shared variable is accessed concurrently by both
 * threads protected by mutex. intentional sleep
 * introduced in thread1 handler so thread2 waits
 * for thread1 to unlock the mutex, and thread2 can
 * acquire mutex.
 */

void * thid1_handler(void *arg)
{
	int ret;
	while (1) {
		printf("%s var: %d\n", __func__, shared_variable);
		printf("%s waiting to acquire mutex..\n", __func__);
		ret = pthread_mutex_lock(&var_mutex);
		if (ret != 0) {
			perror("mutex_lock");
		}
		printf("%s acquired mutex\n", __func__);
		shared_variable = shared_variable + 3;
		sleep(10);
		pthread_mutex_unlock(&var_mutex);

	}
}

void * thid2_handler(void *arg)
{
	int ret;
	while (1) {
		printf("%s var: %d\n", __func__, shared_variable);
		printf("%s waiting to acquire mutex..\n", __func__);
		ret = pthread_mutex_lock(&var_mutex);
		if (ret != 0) {
			perror("mutex_lock");
		}
		printf("%s acquired mutex\n", __func__);
		shared_variable--;
		pthread_mutex_unlock(&var_mutex);
		sleep(4);
	}
}
int main(int argv, char *argc[])
{
	pthread_t thid[2];
	int ret;

	ret = pthread_create(&thid[0], NULL, thid1_handler, NULL);
	if (ret == -1) {
		perror("Thread1 creation failed:\n");
		return -1;
	}

	ret = pthread_create(&thid[1], NULL, thid2_handler, NULL);
	if (ret == -1) {
		perror("Thread1 creation failed:\n");
		return -1;
	}

	ret = pthread_mutex_init(&var_mutex, NULL);
	if (ret != 0) {
		perror("error init mutext\n");
		return -1;
	}

	pthread_join(thid[0], NULL);
	pthread_join(thid[1], NULL);

	ret = pthread_mutex_destroy(&var_mutex);
	if (ret != 0) {
		perror("mutex destroy error");
		return -1;
	}
}
