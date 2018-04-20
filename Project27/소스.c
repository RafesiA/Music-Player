#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#define MAX_CHAR_PER_LINE 1000



// 연결 리스트
typedef struct {
	char data[MAX_CHAR_PER_LINE];
} dataName; // 해당 파일이름, 길이지정

//노드
typedef struct Node {
	dataName data;
	struct Node *link;
} Node;

// 노드 포인터
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

void remove_node(Node **phead, Node *p, Node *removed) {
	if (p == NULL) {
		*phead = (*phead)->link;
	}
	else  p->link = removed->link;

	free(removed);
}

void init(LinkedList *list) {
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}

void reverse_lines(Node **phead) {
	if (*phead == NULL) {
		printf("노드가 없습니다.\n");
		return;
	}
	struct Node *p, *q, *r;

	p = q = r = *phead;
	p = p->link->link;
	q = q->link;
	r->link = NULL;
	q->link = r;

	while (p != NULL) {
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	*phead = q;
}

int get_length(LinkedList *list) {
	return list->length;
}

Node *get_node_at(LinkedList *list, int pos) {
	int i;
	Node *tmp_node = list->head;
	if (pos < 0) return NULL;
	for (i = 0; i < pos; i++) {
		tmp_node = tmp_node->link;
	}
	return tmp_node;
}


void add(LinkedList *list, int position, dataName addData) {
	Node *p;
	if ((position >= 0) && (position <= list->length)) {
		Node *node = (Node *)malloc(sizeof(Node));
		if (node == NULL) printf("메모리 할당에러");
		node->data = addData;
		p = get_node_at(list, position - 1);
		insert_node(&(list->head), p, node);
		list->length++;
	}
}


void add_last(LinkedList *list, dataName data) {
	add(list, get_length(list), data);
}

void add_first(LinkedList *list, dataName data) {
	add(list, 0, data);
}

int is_empty(LinkedList *list) {
	if (list->head == NULL) {
		return 1;
	}
	else return 0;
}

void delete(LinkedList *list, int pos) {
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {
		Node *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
	}
}



int main() {
	LinkedList buffer;
	init(&buffer);
	while (1) {
		
	}
	
}