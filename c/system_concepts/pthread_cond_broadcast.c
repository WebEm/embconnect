// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


/*
 * pthread_cond_broadcast()
 * These functions shall unblock threads blocked on a condition variable.
 *
 * The pthread_cond_broadcast() function shall unblock all threads currently 
 * blocked on the specified condition variable cond.
 *  
 * The pthread_cond_signal() function shall unblock at least one of the threads
 * that are blocked on the specified condition variable cond 
 * (if any threads are blocked on cond).
 *  
 *  If more than one thread is blocked on a condition variable,
 *  the scheduling policy shall determine the order in which threads are unblocked.
 *  When each thread unblocked as a result of a pthread_cond_broadcast() or
 *  pthread_cond_signal() returns from its call to pthread_cond_wait() or
 *  pthread_cond_timedwait(), the thread shall own the mutex with 
 *  which it called pthread_cond_wait() or pthread_cond_timedwait(). 
 *  The thread(s) that are unblocked shall contend for the mutex 
 *  according to the scheduling policy (if applicable), 
 *  and as if each had called pthread_mutex_lock().
 *  
 *  The pthread_cond_broadcast() or pthread_cond_signal()
 *  functions may be called by a thread whether or not it currently owns 
 *  the mutex that threads calling pthread_cond_wait() or 
 *  pthread_cond_timedwait() have associated with the condition variable 
 *  during their waits; however, if predictable scheduling behavior is required, 
 *  then that mutex shall be locked by the thread calling 
 *  pthread_cond_broadcast() or pthread_cond_signal().
 *  
 *  The pthread_cond_broadcast() and pthread_cond_signal() 
 *  functions shall have no effect if there are no threads currently 
 *  blocked on cond.
 *  
 */

pthread_cond_t cond;
pthread_mutex_t mutex;

void * thid1_handler(void *arg)
{
	while (1) {
		printf("%s and signall the waiting threads.\n", __func__);
		if(pthread_cond_broadcast(&cond)) {
			printf("error in signall broadcast.");
		}
		sleep(6);
	}
}

void * thid2_handler(void *arg)
{
	while (1) {
		printf("%s and waiting for signall......\n", __func__);
		pthread_cond_wait(&cond, &mutex);
		printf("%s rcvd signall......\n", __func__);
	}
}

void * thid3_handler(void *arg)
{
	while (1) {
		printf("%s and waiting for signall....\n", __func__);
		pthread_cond_wait(&cond, &mutex);
		printf("%s rcvd signall......\n", __func__);
	}
}

int main(int argv, char *argc[])
{
	pthread_t thid[3];
	int ret;

	ret = pthread_create(&thid[0], NULL, thid1_handler, NULL);
	if (ret == -1) {
		perror("thread creation failed \n");
		return -1;
	}

	ret = pthread_create(&thid[1], NULL, thid2_handler, NULL);
	if (ret == -1) {
		perror("thread1 creation failed \n");
		return -1;
	}

	ret = pthread_create(&thid[2], NULL, thid3_handler, NULL);
	if (ret == -1) {
		perror("thread2 creation failed\n");
		return -1;
	}

	pthread_join(thid[0], NULL);
	pthread_join(thid[1], NULL);
	pthread_join(thid[2], NULL);

}

