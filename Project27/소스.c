#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_CHAR_PER_LINE 1000

typedef char dataName[MAX_CHAR_PER_LINE];

typedef struct Node {
	dataName;
	struct Node *link;
} Node;

typedef struct LinkedList {
	Node *head;
	int length;
} LinkedList;

void insert_node(Node **phead, Node *p, Node *new_node) {
	if (*phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}