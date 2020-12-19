
// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct timespec t;
time_t tv;

void * thid1_handler(void *arg)
{
	/*
	 * intentionally Not signalling
	 * so cond will be timedout.
	 */
	while (1) {
		pthread_mutex_lock(&mutex);
		time(&tv);
		t.tv_sec = tv + 4;
		pthread_cond_timedwait(&cond, &mutex, &t);
		printf("Timed out.....\n");
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argv, char *argc[])
{
	pthread_t thid;
	int ret;

	ret = pthread_create(&thid, NULL, thid1_handler, NULL);
	if (ret != 0) {
		perror("Thread creation failed");
	}

	pthread_join(thid, NULL);
}
