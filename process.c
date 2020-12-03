// program to create a process using fork()

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

