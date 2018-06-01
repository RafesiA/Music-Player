#include <iostream>
#include <cstdlib>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>


#define MAX_CHAR_PER_LINE 1000
using namespace std;


typedef struct {
	char data[MAX_CHAR_PER_LINE];
} dataName;

class Node {
public:
	dataName data;
	Node *link;
};

class LinkedList {
private:
	Node * head;
	int length;
	string line;

public:
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
			if (node == NULL) cout << "메모리 할당에러";
			node->data = addData;
			p = get_node_at(list, position - 1);
			insert_node(&(list->head), p, node);
			list->length++;
		}
	}

	void _delete(LinkedList *list, int pos) {
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
		string mystr;
		char line[MAX_CHAR_PER_LINE];
		dataName d;

		cout << "Choose number to input: ";
		cin >> pos;
		pos -= 1;
		cout << "input .wav File to add list: ";

		getline(cin, mystr);
		fflush(stdin);

		fgets(line, MAX_CHAR_PER_LINE, stdin);
		strcpy(d.data, line);
		add(buffer, pos, d);

	}

	void delete_music(LinkedList *buffer) {
		int pos;

		if (is_empty(buffer)) {
			cout << "Theres no musics." << endl;
		}
		else {
			cout << "Delete music number: ";
			cin >> pos;
			_delete(buffer, pos - 1);
		}
	}

	void play(LinkedList *buffer) {
		sf::SoundBuffer sbf;
		Node *tmp;
		tmp = buffer->head;
		int i;
		int pos;
		cout << "Play music number: ";
		cin >> pos;
		int length = buffer->length;

		if (pos != NULL) {
			for (i = 0; i <= pos; i++) {
				if (i == pos - 1) {
					cout << "File Name Is : " << tmp->data.data << endl;
					string target = tmp->data.data;

					sf::Sound music;
					if (!sbf.loadFromFile("Hopes and Dreams.wav")) {
						cout << "Error occured!" << endl;
					}
					else {
						music.setBuffer(sbf);
						cout << "Now Playing : " << target << endl;
						music.play();
					}
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

		cout << "***** Player List *****" << endl;
		for (i = 0; i < buffer->length; i++) {
			cout << tmp_node->data.data;
			tmp_node = tmp_node->link;
		}
		cout << "********************" << endl;
	}

};


void showMenu() {
	cout << "\nMusic Player Based on Console \n" << endl;
	cout << "*********Select Menu********" << endl;
	cout << "0. Exit Music Player" << endl;
	cout << "1. Add Music" << endl;
	cout << "2. Delete Music from List" << endl;
	cout << "3. Play Music" << endl;
	cout << "4. Play Random Music" << endl;
	cout << "5. Show Current List" << endl;
}



void menu(int i, LinkedList *buffer) {
	LinkedList list;
	switch (i) {
	case 1:
		list.insert_music(buffer);
		break;
	case 2:
		list.delete_music(buffer);
		break;
	case 3:
		list.play(buffer);
		break;
	case 4:
		break;
	case 5:
		list.display(buffer);
		break;
	case 0:
		break;
	default:
		cout << "Wrong Select!" << endl;
		break;
	}
}



int main() {
	int input;
	LinkedList buffer;
	buffer.init(&buffer);

	do {
		showMenu();
		scanf("%d", &input);
		menu(input, &buffer);
		fflush(stdin);
	} while (input != 0);
	if (input == 0) {
		cout << "Program Closed" << endl;
	}
}