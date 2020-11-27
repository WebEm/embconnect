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
	struct node *prev;
};

struct node *head;
struct node *tail;

int add_node(int data)
{
	struct node *newnode;
	struct node *temp;
	struct node *prev;

	newnode = (struct node *)malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Failure in mem allocation\n");
		return -ENOMEM;
	}
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->data = data;

	if (head == NULL) {
		head = newnode;
		tail = newnode;
	} else {
		temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newnode;
		newnode->next = NULL;
		newnode->prev = temp;
		tail = newnode;
	}


}

void print_list_forward(void)
{
	struct node *temp = head;

	while (temp != NULL) {
		printf("data: %d\n", temp->data);
		temp = temp->next;
	}
}

void print_list_backward(void)
{
	struct node *temp = tail;

	while (temp != NULL) {
		printf("data: %d\n", temp->data);
		temp = temp->prev;
	}
}

int main(int argv, char *argc[])
{
	add_node(10);
	add_node(20);
	add_node(100);
	add_node(400);
	add_node(500);
	add_node(600);
	print_list_forward();
	printf("travers list backward.....\n");
	print_list_backward();
}
