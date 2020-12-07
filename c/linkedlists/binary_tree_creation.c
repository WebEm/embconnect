
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
	struct node *lchild;
	struct node *rchild;
};

struct node *root = NULL;

/*
 * binary tree thumb rule
 * will not have any duplicate data
 * Inorder traversal will always give the sorted order.
 * if the data is lesser than than the root node it is inserted
 * in the right side of the node
 * if the data is greater than the root nide it is inserted in
 * the left side of the node
 */

int insert(int data)
{
	struct node *newnode;
	struct node *temp;
	struct node *q;

	newnode = (struct node *)malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Mem allocation failed\n");
		return -ENOMEM;
	}

	newnode->data = data;
	newnode->lchild = NULL;
	newnode->rchild = NULL;

	if (root == NULL) {
		root = newnode;
	} else {
		temp = root;
		while (temp != NULL) {
			q = temp;
			if (data > temp->data) {
				temp = temp->rchild;
			} else if (data < temp->data) {
				temp = temp->lchild;
			} else {
				printf("data already available so discarding...\n");
				return 0;
			}
		}

		if (data > q->data)
			q->rchild = newnode;
		else
			q->lchild = newnode;
	}
}

/*
 * in order traversal using recursion logic
 */

void display_inorder_rbinary_tree(struct node *root)
{
	if (root) {
		display_inorder_rbinary_tree(root->lchild);
		printf("data: %d\n", root->data);
		display_inorder_rbinary_tree(root->rchild);
	}
}

int main(int argv, char *argc[])
{
	int a[] = {1, 10, 5, 5, 7, 8, 11, 3, 2, 22, 43, 87, 90, 55, 5, 10};
	int i;

	for (i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
		insert(a[i]);
	}
	display_inorder_rbinary_tree(root);
}
