// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argv, char *argc[])
{
	pid_t pid;
	int i = 20;

	pid = fork();
	if (pid == 0) {
		/* 
		 * Child process.
		 * Fork() returns zero to child process and child's PID to Parent thread
		 * upon successfull process creation child process will have it's own 
		 * address space. Once the process is created parent can communicate to child
		 * only through Inter process communication / over sockets.
		 */
		while (i--) {
			printf("I am child process\n");
			sleep(1);
		}
	} else {
		printf("Childs process id is %d\n", pid);
		printf("Parent waiting for child to exit\n");
		wait(0); //wait for child to exit
		printf("Child exited\n");
	}
}

