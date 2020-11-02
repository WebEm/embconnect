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
	struct node *newnode;
	struct node *temp;

	newnode = (struct node *)malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Error in creating new node\n");
		return -ENOMEM;
	}

	if (head == NULL) {
		head = newnode;
		newnode->data = data;
		newnode->next = NULL;
	}
	temp = head;
	while (temp->next != NULL)
		temp = temp->next;

	temp->next = newnode;
	newnode->data = data;
	newnode->next = NULL;

	return 0;
}

void print_list(void)
{
	struct node *temp = head;

	if (head == NULL) {
		printf("list empty......\n");
		return;
	}

	while (temp != NULL) {
		printf("data :: %d\n", temp->data);
		temp = temp->next;
	}
}

int count_list(void)
{
	int count = 0;
	struct node *temp;

	temp = head;

	if (temp) {
		while (temp) {
			count++;
			temp = temp->next;
		}
	} else {
		count = 0;
	}
	return count;
}

void delete_node(int pos)
{
	int count, i = 1;
	struct node *temp = head;
	struct node *prev;

	count = count_list();
	if (pos > count) {
		printf("list count:%d\n", count);
		return;
	}

	printf("delete node pos: %d\n", pos);

	/* First node deletion*/
	if (pos == 1) {
		temp = head;
		head = temp->next;
		free(temp);
		return;
	}

	while (temp) {
		prev = temp;
		temp = temp->next;
		i++;
		if (pos == i) {
			prev->next = temp->next;
			free(temp);
			break;
		}
	}

}

int main(int argv, char *argc[])
{
	print_list();
	add_node_end(5);
	add_node_end(10);
	add_node_end(15);
	add_node_end(20);
	add_node_end(25);
	add_node_end(30);
	add_node_end(35);
	add_node_end(40);
	add_node_end(45);
	add_node_end(50);
	print_list();
	delete_node(2);
	print_list();

	return 0;
}
