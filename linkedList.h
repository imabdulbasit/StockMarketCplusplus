#pragma once
#include "includes.h"
using namespace std;

class listnode {        //class for listnode of linked list
public:
	char* value;
	listnode* next = NULL;
};
class list {
public:
	listnode* head;
public:
	list() {  // default constructor assigning NULL to head
		head = NULL;
	}

	~list() {}
	void insertathead(char* a) {// function to insert listnode at head

		if (!head) {  //checking if list is empty
			head = (new listnode);
			head->value = a;
			head->next = NULL;
		}
		else {
			listnode* temp = new listnode;
			temp->value = a;
			temp->next = head;
			head = temp;

		}
	}
	void displaylist() {
		if (head == NULL) {
			cout << "List is empty!" << endl;
			return;
		}
		listnode* temp = head;
		while (temp != NULL) {
			cout << temp->value << " ";
			temp = temp->next;
		}
		cout << endl;
	}

	void insertatlocation(int location, char* value) {//function to insert listnode at a specific location
		int count = 0;
		listnode* temp = head;
		while (1) {
			if (location == 0) {
				insertathead(value);
				break;
			}
			if (count < location && temp == NULL) {
				cout << "index greater than length of linked list" << endl;
				break;
			}

			if (count == location - 1) {
				listnode* add = new listnode;
				add->value = value;
				add->next = temp->next;
				temp->next = add;
				break;
			}
			count++;
			temp = temp->next;


		}

	}

	void del(int index) {// function to delete a specific listnode with given index

		int count = 0;
		listnode* temp = head;
		bool flag = true;
		while (temp != NULL) {
			if (index == 0) {
				head = temp->next;
				delete temp;
				flag = false;
				break;

			}
			if (count == index - 1) {
				listnode* a = temp->next;
				temp->next = temp->next->next;
				delete a;
				flag = false;
				break;
			}
			temp = temp->next;
			count++;
		}
		if (flag) {
			cout << "Index Greater than length of Linked list" << endl;
		}
	}
	int countlist() { // function to print length of linked list
		int count = 0;
		listnode* temp = head;
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}
		return count;
	}

	char* atindex(int i) {
		if (i > countlist()) {
			return NULL;
		}
		else {
			listnode* l;
			l = head;
			for (int j = 0; j < i-1; j++) {
				l = l->next;
			}
			return l->value;
		}
	}
};

