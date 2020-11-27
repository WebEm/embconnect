/*
 *   circular_linked_list.c
 * 
 * 2016+ Copyright (c) WebEm <embconnect001@gmail.com>
 * All rights reserved.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * simple program to demonstrate circular linked list.c
 * Last node in the list poitig to the head.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define debug 1
#ifdef debug
#define dbg printf
#else
#define dbg
#endif

/* Globals */
struct node {
	int data;
	struct node *head;
	struct node *next;
};

struct node *head = NULL;
/*
 * Prototypes
 */
void* alloc(size_t size);
int create_node(void);
void link_node(struct node *node);
void print_node(void);
void assign_data(void);

int main(int argv, char *argc[])
{
	int i;
	int no_of_node;

	printf ("Enter the no of nodes to create and link:\n");
	scanf("%d", &no_of_node);
	for (i = 0; i < no_of_node; i++)
		create_node();

	assign_data();
	print_node();
}

void print_node(void)
{
	struct node *tmp;
	tmp = head;
	while(tmp->next != head) {
		printf("node addr:%p node->next: %p data: %d\n",
					tmp, tmp->next, tmp->data);
		tmp = tmp->next;
	}
	/* 
	 * Need a better logic here
	 */
	printf("node addr:%p node->next: %p data: %d\n",
				tmp, tmp->next, tmp->data);
	
}

void link_node(struct node *node)
{
	struct node *temp;
	if (!head) {
		head = node;
	} else {
		temp = head;
		while (temp->next != head)
			temp = temp->next;
		temp->next = node;
		node->next = head;
		
	}
	node->head = head;
}

int create_node(void)
{
	struct node *newnode;
	newnode = alloc(sizeof(struct node));
	if (!newnode)
		return -1;
	newnode->next = newnode;
	link_node(newnode);
}

void assign_data(void)
{
	struct node *tmp = head;
	int data;

	while(tmp->next != head) {
		printf("Data:\n");
		scanf("%d", &data);
		tmp->data = data;
		tmp = tmp->next;
	}
	/* 
	 * Need a better logic here
	 */
	printf("Data:\n");
	scanf("%d", &data);
	tmp->data = data;
	
}

/*
 * Wrapper to malloc
 */
void* alloc(size_t size)
{
	char *ptr;
	ptr = malloc(size);
	if (ptr) {
		dbg("memory allocated at %p\n", ptr);
	} else {
		printf("Memory allocation failed\n");
		return NULL;
	}
	return ptr;
}
