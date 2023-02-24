#include<stdio.h>
#include<stdlib.h>
struct Node
{
	int data;
	struct Node*next;
};
void push(struct Node**head_rf,int new_data)
{
	struct Node*new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head_rf);
	(*head_rf) = new_node;
}
void addAfter(struct Node*prev_node,int new_data)
{
	if (prev_node == NULL) {
		printf("previous node not NULL");
		return;
	}
	struct Node*new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}
void addend(struct Node**head_rf,int new_data)
{
	struct Node*new_node = (struct Node*)malloc(sizeof(struct Node));
	struct Node*last = *head_rf;
	new_node->data = new_data;
	new_node->next = NULL;
	if (*head_rf == NULL) {
		*head_rf = new_node;
		return;
	} while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	return;
}
void printList(struct Node *node)
{
	while (node != NULL) {
	printf("%d", node->data);
	node = node->next;
        }
}
int main()
{
	struct Node* head = NULL;
	addend(&head,1);
	push(&head,2);
	push(&head,3);
	addend(&head,4);
	addAfter(head->next,5);
	printf("\n enter linked list is:");
	printList(head);
	return 0;
}



