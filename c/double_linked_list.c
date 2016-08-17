/*
 *   double_linked_list.c
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
 * Simple program to demonstrate double linked list.
 * next node and prev node address are maintained.
 * This program is just for understanding. Need not look in to 
 * optimization point of veiw.
 * Will upload optimized logic later???
 */
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 1
#ifdef DEBUG
#define dbg printf
#else 
#define dbg
#endif
/*
 * Globals
 */
struct node {
	int data;
	struct node *next;
	struct node *prev;
	struct node *head;
};

struct node *head = NULL;
/*
 * Prototypes 
 */
int create_node_and_link(int no_of_nodes);
void display_fwd_rev(void);

int main(int argv, char *argc[])
{
	int no_of_nodes;

	printf("Enter no of nodes to create\n");
	scanf("%d", &no_of_nodes);
	create_node_and_link(no_of_nodes);
	display_fwd_rev();
}

/*
 * Create_node_and_link function will create a newnode
 * and updates the next pointer to the next node and the 
 * prev pointer to the prev node.
 * Return -1 on failure, 0 on success.
 */
int create_node_and_link(int no_of_nodes)
{
	struct node *newnode;
	struct node *tmp;
	int i;
	/*
	 * Default err checks.
	 */
	if (no_of_nodes < 0) {
		dbg("node legnth should be always greater/equal to 1\n");
		return -1;
	}

	for (i = 0; i <= no_of_nodes; i++) {
		newnode = malloc(sizeof(struct node));
		if (!newnode) {
			dbg("memory allocation failed for the newnode\n");
			return -1;
		}
		dbg("memory allocated @ %p i: %d\n", newnode, i);
		newnode->next = NULL;
		newnode->prev = NULL;
		newnode->data = i;

		if (head == NULL) {
			head = newnode;
		} else {
			tmp = head;
			while (tmp->next != NULL) {
				tmp = tmp->next;
			}
			tmp->next = newnode;
			newnode->prev = tmp;
		}
	}
	return 0;
}

void display_fwd_rev(void)
{
	struct node *tmp;
	tmp = head;
	while (tmp->next != NULL) {
		printf ("addr: %p addr->next: %p addr->prev: %p addr->data: %d\n",
				tmp, tmp->next, tmp->prev, tmp->data);
		tmp = tmp->next;
	}	

	printf("Walk back.....\n");

	while (tmp->prev != NULL) {
		printf ("addr: %p addr->next: %p addr->prev: %p addr->data: %d\n",
				tmp, tmp->next, tmp->prev, tmp->data);
		tmp = tmp->prev;
	}
	printf ("addr: %p addr->next: %p addr->prev: %p addr->data: %d\n",
			tmp, tmp->next, tmp->prev, tmp->data);
}

