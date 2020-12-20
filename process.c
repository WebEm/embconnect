// program to create a process using fork()

// SPDX-License-Identifier: GPL-2.0+
/*
 2020+ Copyright (c)
 All rights reserved.
*/

#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 

void main() 
{ 
    int process = fork(); 
    if (process >= 0) {
            if (process == 0)
                printf("This is the child process...\n");
            else
                printf("This is the parent process...\n");
    }
    else
            perror("fork");
} 

