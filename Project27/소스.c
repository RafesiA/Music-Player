
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <ctype.h>
#pragma comment(lib, "winmm.lib")

#define MAX_CHAR_PER_LINE 1000



// 연결 리스트 데이터 지정
typedef struct {
	char data[MAX_CHAR_PER_LINE];
} dataName; // 해당 파일이름, 길이지정

//노드 구성, data && link
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

	printf("Reverse sort successful.\n\n");
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

void delete(LinkedList *list, int pos) {
	if (!is_empty(list) && (pos >= 0) && (pos < list->length)) {
		Node *p = get_node_at(list, pos - 1);
		remove_node(&(list->head), p, (p != NULL) ? p->link : NULL);
		list->length--;
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

void insert_music(LinkedList *buffer) {
	int pos;
	char line[MAX_CHAR_PER_LINE];
	dataName d;
	
	printf("Choose number to input:\n ");
	scanf("%d", &pos);
	pos -= 1;
	printf("Input .wav File to add list\n ");
	gets(stdin);
	fflush(stdin);
	fgets(line, MAX_CHAR_PER_LINE, stdin);
	strcpy(d.data, line);
	add(buffer, pos, d);
	
}

void delete_music(LinkedList *buffer) {
	int pos;

	if (is_empty(buffer)) {
		printf("Theres no musics.\n");
	}
	else {
		printf("Delete music number: ");
		scanf("%d", &pos);
		delete(buffer, pos - 1);
	}
}

void play(LinkedList *buffer) {
	Node *tmp;
	tmp = buffer->head;
	int i;
	int pos;
	printf("Play music number: ");
	scanf("%d", &pos);
	int length = buffer->length;

	if (pos == 1) {
		printf("File name is %s", tmp->data.data);
	}
	else {
		for (i = 0; i <= pos; i++) {
			if (i == pos - 1) {
				printf("File Name Is : %s", tmp->data.data);
				break;
			}
			tmp = tmp->link;
		}
	}
}



void display(LinkedList *buffer) {
	int i;
	Node *tmp_node;
	tmp_node = buffer->head;

	printf("*****Player List*****\n");
	for (i = 0; i < buffer->length; i++) {
		printf("%s", tmp_node->data.data);
		tmp_node = tmp_node->link;
	}
	printf("********************\n");
}

void showMenu() {
	printf("\nMusic Player Based on Console\n\n");
	printf("*********Select Menu********\n");
	printf("0. Exit Music Player\n");
	printf("1. Add Music\n");
	printf("2. Delete Music from List\n");
	printf("3. Play Music\n");
	printf("4. Play Random Music\n");
	printf("5. Reverse Play List\n");
	printf("6. Show Current List\n");
}



void menu(int i, LinkedList *buffer) {
	switch (i) {
	case 1:
		printf("You chosen number 1\n\n");
		insert_music(buffer);
		break;
	case 2:
		delete_music(buffer);
		break;
	case 3:
		play(buffer);
		break;
	case 4:
		break;
	case 5:
		reverse_lines(buffer);
		break;
	case 6:
		display(buffer);
	}
}



int main() {
	int input;
	LinkedList buffer;
	init(&buffer);

	do {
		showMenu();
		scanf("%d", &input);
		menu(input, &buffer);
	} while (input != 0);
	if (input == 0) {
		printf("Program Closed");
	}
}