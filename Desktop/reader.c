// IPC using shared memory- Read Program

// SPDX-License-Identifier: GPL-2.0+
/*
 2020+ Copyright (c) gayathri-bytes <gaya3velu.25@gmail.com>
 All rights reserved.
*/

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int returnval, shmid;
    void *mem = NULL;
    char *p;
    shmid = shmget((key_t)1234, 100, IPC_CREAT|0666);
    if (shmid < 0) {
        printf("Key creation failed");
        shmid = shmget((key_t)1234, 6, 0666);
    }
    mem = shmat(shmid, NULL, 0);
    p = (char *)mem;
    if (p == NULL) {
        printf("Attachment Failed");
        return 0;
    }
    printf ("\n MESSAGE: %s", p);
    returnval = shmdt(p);
    if (returnval < 0) {
        printf("Detachment failed");
        return 0;
    }
    returnval = shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
