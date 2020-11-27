// SPDX-License-Identifier: GPL-2.0+
/*
 * 2020+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct node {
	int data;
	struct node *next;
};

struct node *head;

int add_node_end(int data)
{
	struct node *temp;
	struct node *newnode;

	newnode = (struct node *)malloc(sizeof(struct node));
	if (newnode == NULL) {
		return -ENOMEM;
	}
	newnode->data = data;

	temp = head;
	if (temp == NULL) {
		head = newnode;
	} else {
		while (temp->next != NULL) {
			temp = temp->next;
		} 
		temp->next = newnode;
		newnode->next = NULL;
	}
}

void display(struct node *node)
{
	if (node != NULL) {
		printf("data= :%d\n", node->data);
		display(node->next);
	}
}

void displayr(struct node *node)
{
	if (node != NULL) {
		displayr(node->next);
		printf("data= :%d\n", node->data);
	}
}

int insert_node(int data, int pos)
{

	struct node *newnode;
	struct node *temp;
	int i;

	newnode = (struct node*)malloc(sizeof(struct node));
	if (!newnode) {
		printf("Error in mem allocation");
		return -ENOMEM;
	}
	newnode->data = data;

	if (pos == 0 && head) {
		printf("updating head...\n");
		newnode->next = head;
		head = newnode;
	} else {
		temp = head;
		for (i = 0; i < (pos -1) && temp; i++) {
			temp = temp->next;
		}
		newnode->next = temp->next;
		temp->next = newnode;
	}
}


int main(int argv, char *argc[])
{
	int a[] = {1, 23, 3, 10, 4, 5, 20, 21, 22, 64, 100};
	int i;
	struct node *temp;

	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
		add_node_end(a[i]);
	}
	temp = head;
	printf("***display forward***\n");
	display(temp);
	printf("***display reverse***\n");
	temp = head;
	displayr(temp);
	printf("***insert begining***\n");
	insert_node(0, 0);
	temp = head;
	display(temp);
	printf("***insert middle***\n");
	insert_node(220, 3);
	temp = head;
	display(temp);
	printf("***insert last***\n");
	insert_node(420, 12);
	temp = head;
	display(temp);
	printf("***insert unknown causes segfault needs to be handled***\n");
	insert_node(520, 30);
	temp = head;
	display(temp);
}
