#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node *head;

int create_list(int data)
{
	struct node *newnode, *temp;

	newnode = (struct node *)malloc(sizeof(struct node));
	if (!newnode) {
		printf("Mem alloc failed\n");
		return -ENOMEM;
	}

	newnode->data = data;
	newnode->next = NULL;

	temp = head;
	if (temp == NULL) {
		head = newnode;
	} else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		newnode->next = temp->next;
		temp->next = newnode;
	}
}

void display_list(struct node *p)
{
	if (p != NULL) {
		printf("data :%d\n", p->data);
		display_list(p->next);
	}
}

/*
 * reversing a linked list using sliding pointers using three temp ptr
 * r, q ,p
 * Initially p is pointing on first node. q and r points to NULL. Three
 * pointers slide together. First r(prev pointer) should come on q,
 * q should move to p. and p is moved to next node. reverse a link(q->next = r )
 * and follow this till p becomes NULL.
 *
 */

void reverse_list_using_sliding_ptr(void)
{
	struct node *p = NULL;
	struct node *q = NULL;
	struct node *r = NULL;

	p = head;

	while (p != NULL) {
		r = q;  // prev node
		q = p;
		p = p->next; // Next node
		q->next = r; //reverse a link
	}
	head = q;
}

int main(int argv, char *argc[])
{
	struct node *temp;
	int a[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	int i;

	for (i = 0; i < (sizeof(a)/sizeof(a[0])); i++) {
		create_list(a[i]);
	}

	temp = head;
	if(temp) {
		display_list(temp);
	}
	printf("****print list in reverse order by chaning links ***\n");
	reverse_list_using_sliding_ptr();
	temp = head;
	if(temp) {
		display_list(temp);
	}
}
