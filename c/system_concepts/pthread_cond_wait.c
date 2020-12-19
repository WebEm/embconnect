// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * thid1_handler(void *arg)
{
	while (1) {
		printf("%s waiting for signal....\n", __func__);
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		printf("I have been signalled.....\n");
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}

}

void * thid2_handler(void *arg)
{
	while (1) {
		printf("%s singnal the thread waiting on condition...\n",
			       				__func__);
		pthread_cond_signal(&cond);
		sleep(3);
	}

}

int main(int argv, char *argc[])
{
	pthread_t thid[2];
	int ret;

	ret = pthread_create(&thid[0], NULL, thid1_handler, NULL);
	if (ret != 0) {
		perror("Thread creation failed\n");
		return -1;
	}

	ret = pthread_create(&thid[1], NULL, thid2_handler, NULL);
	if (ret != 0) {
		perror("Thread creation failed\n");
		return -1;
	}

	pthread_join(thid[0], NULL);
	pthread_join(thid[1], NULL);

}
