/*
 *   node_deletion.c
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
 * node deletion in single linked list.
 * Not a optimized code.
 * just for understanding the concept.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 * uncommet to turn on debug
 */
#define DEBUG
#ifdef DEBUG
#define dbg printf
#else
#define dbg
#endif

struct list {
	int data;
	struct list *next;
};

/* Globals */
struct list *head = NULL;

/* proto types */
int create_list(int node);
void print_list(void);
void node_del(int pos);

int main(int argv, char *argc[])
{
	int node;
	int pos;
	printf("No of nodes to create\n");
	scanf("%d", &node);
	create_list(node);
	print_list();

	while (1) {
		printf("Node pos to delete\n");
		scanf("%d", &pos);
		node_del(pos);
		printf("list after deletion\n");
		print_list();
	}
}

/*
 * Create list will create the number of nodes specified in
 * the argument and links to the subsequent node with last node
 * pointing to NULL.
 */
int create_list(int no_of_nodes)
{
	struct list *temp = NULL;
	struct list *newnode = NULL;
	int i;
	
	for (i = 0; i < no_of_nodes; i++) {
		newnode = malloc(sizeof(struct list));
		newnode->next = NULL;
		newnode->data = i + 1;
		dbg("newnode addr: %p\n", newnode);
		if (!newnode) {
			printf("Memory allocation failed\n");
			return -ENOMEM;
		}
		if (!head) {
			head = newnode;
		} else {
			temp = head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = newnode;
		}
	}
}

void print_list(void)
{
	struct list *temp = head;
	while (temp) {
		dbg("temp addr %p\n", temp);
		printf("The val is:%d\n", temp->data);
		temp = temp->next;
	}
}

void node_del(int pos)
{
	struct list *tmp = head;
	struct list *prev = tmp;
	int i = 1;

	while (i != pos) {
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
	/*
	 * last pos delition to be handled.
	 */
	if (i == 1 && tmp->next)
		head = tmp->next;

	if (tmp) {
		prev->next = tmp->next;
		free(tmp);
	}
}
