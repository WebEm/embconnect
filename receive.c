//IPC using message queque
//Receiver of the message

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

int main(int argc, char *argv[]) 
{ 
	key_t qkey; 
	float a, b, c;
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
	msgrcv(msgid, &message, sizeof(message), 1, 0); 
	char op = *message.msg_text;
	if (argc<=1) {
        printf("Input the numbers");
        exit(1);
    }  
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	if (op == '+') {
	        c = a + b;
	}
	if (op == '-') {
	        c = a - b;
	}
	if (op == '*') {
	        c = a * b;
	}
	if (op == '/') {
	        c = a / b;
	}
	printf("The operation to be performed is: %s and the answer is: %f\n", 
	                message.msg_text, c); 
	msgctl(msgid, IPC_RMID, NULL); 
    return 0; 
} 

