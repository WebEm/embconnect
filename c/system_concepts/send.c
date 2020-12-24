//IPC using message queque
//Sender of the message

// SPDX-License-Identifier: GPL-2.0+
/*
 2020+ Copyright (c) gayathri-bytes <gaya3velu.25@gmail.com>
 All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 200 

struct pro_msg { 
	long msg_type; 
	char msg_text[MAX]; 
} message; 

int main() 
{ 
	key_t qkey; 
	int msgid; 
	qkey = ftok("send.c", 65); 
	msgid = msgget(qkey, 0666 | IPC_CREAT); 
	if (qkey == -1) {
        	perror("qkey");
        	exit(1);
        } 
        if (msgid == -1) {
        	perror("msgid");
        	exit(1);
    	}
        printf("Operation to be performed: "); 
	message.msg_type = 1; 
	fgets(message.msg_text, MAX, stdin); 
	msgsnd(msgid, &message, sizeof(message), 0);
	return 0; 
} 

