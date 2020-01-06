#pragma once
#include "includes.h"
#include <algorithm>
#include <stack>

class BST
{
private:
	struct node {
		struct node* left;
		struct node* right;
		char* data;
		int volume;
		int high, low, open, close;
		int height;
	};


	void makeEmpty(node* t)
	{
		if (t == NULL)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	node* insert(char* x, node* t  , int volume, int high, int low, int open, int close)
	{
		if (t == NULL)
		{
			t = new node;
			t->data = x;
			t->volume = volume;
			t->open = open;
			t->close = close;
			t->low = low;
			t->high = high;
			t->height = 0;
			t->left = t->right = NULL;
		}

		
		else if (strcmp(x, t->data) < 0)
		{
			t->left = insert(x, t->left, volume, high, low, open, close);
			if (height(t->left) - height(t->right) == 2)
			{
				if (strcmp(x, t->left->data) < 0)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else if (strcmp(x, t->data) > 0)
		{
			t->right = insert(x, t->right, volume, high, low, open, close);
			if (height(t->right) - height(t->left) == 2)
			{
				if (strcmp(x, t->right->data) > 0)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRightRotate(node*& t)
	{
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), t->height) + 1;
		return u;
	}

	node* singleLeftRotate(node*& t)
	{
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		return u;
	}

	node* doubleLeftRotate(node*& t)
	{
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node* doubleRightRotate(node*& t)
	{
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(char* x, node* t)
	{
		node* temp;

		// Element not found
		if (t == NULL)
			return NULL;

		// Searching for element
		else if (strcmp(x, t->data) < 0)
			t->left = remove(x, t->left);
		else if (strcmp(x, t->data) > 0)
			t->right = remove(x, t->right);

		// Element found
		// With 2 children
		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->data = temp->data;
			t->right = remove(t->data, t->right);
		}
		// With one or zero child
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
		}
		if (t == NULL)
			return t;

		t->height = max(height(t->left), height(t->right)) + 1;

		// If node is unbalanced
		// If left node is deleted, right case
		if (height(t->left) - height(t->right) == 2)
		{
			// right right case
			if (height(t->left->left) - height(t->left->right) == 1)
				return singleLeftRotate(t);
			// right left case
			else
				return doubleLeftRotate(t);
		}
		// If right node is deleted, left case
		else if (height(t->right) - height(t->left) == 2)
		{
			// left left case
			if (height(t->right->right) - height(t->right->left) == 1)
				return singleRightRotate(t);
			// left right case
			else
				return doubleRightRotate(t);
		}
		return t;
	}

	int height(node* t)
	{
		return (t == NULL ? -1 : t->height);
	}

	int getBalance(node* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}
	int count( node* root) {
		if (root == NULL) {
			return 0;
		}
		else {
			return 1 + count(root->left) + count(root->right);
		}
	}
	void inorder(node* t)
	{
		if (t == NULL)
			return;
		inorder(t->left);
		cout << "Ticker :  " << t->data << " " ;
		cout << "Volume :  " << t->volume << " ";
		cout << "Daily High :  " << t->high << " ";
		cout << "Daily Low :  " << t->low << " ";
		cout << "Open :  " << t->open << " ";
		cout << "Close :  " << t->close << endl;
		inorder(t->right);
	}

	 node* search( node* t, char* key)
	{
		
		 node* current = new node;
		 current = t;

		 while (current && (strcmp(current->data, key) != 0)) {
			 if (strcmp(key, current->data) > 0)
				 current = current->right;
			 else
				 current = current->left;
		 }
		 return current;
	}

	 void saveFile(node* root)
	 {
		 stack<node*> s;
		 node* curr = root;
		 ofstream file;
		 file.open("example44.txt");
		 while (curr != NULL || s.empty() == false)
		 {
			 /* Reach the left most Node of the
				curr Node */
			 while (curr != NULL)
			 {
				 /* place pointer to a tree node on
					the stack before traversing
				   the node's left subtree */
				 s.push(curr);
				 curr = curr->left;
			 }

			 /* Current must be NULL at this point */
			 curr = s.top();
			 s.pop();
			 char buffer[14];
			 char buffer1[14];
			 char buffer2[14];
			 char buffer3[14];
			 char buffer4[14];

			 snprintf(buffer, 14, "%d", curr->volume);

			 file << curr->data << " ";
			 file << buffer << " ";
			 snprintf(buffer1, 14, "%d", curr->open);
			 file << buffer1 << " ";
			 snprintf(buffer2, 14, "%d", curr->close);
				 file << buffer2 << " ";

			 snprintf(buffer3, 14, "%d", curr->high);
			 file << buffer3 << " ";

			 snprintf(buffer4, 14, "%d", curr->low);
			 file << buffer4 << " ";
			 file << "\n";
			// delete buffer, buffer1, buffer2, buffer3, buffer4;
			 /* we have visited the node and its
				left subtree.  Now, it's right
				subtree's turn */
			 curr = curr->right;

		 } /* end of while */
		 file.close();
	 }

public:
	node* root;

	BST()
	{
		root = NULL;
	}

	void insert(char* x , int volume, int high, int low, int open, int close)
	{
		root = insert(x, root , volume, high, low, open, close);
	}

	void remove(char* x)
	{
		root = remove(x, root);
	}

	void display()
	{
		inorder(root);
		cout << endl;
	}

	node* search__(char* key) {
		return (search(root, key));
	}

	void displaynode(char* x) {
		node * temp  = search__(x);
		if (temp != NULL) {
			printf("\n Ticker : %s Volume : %d  Open : %d Close : %d Daily High : %d Daily Low : %d\n", temp->data, temp->volume, temp->open, temp->close, temp->high, temp->low);
		}
		else {
			printf("\n Not found!");
		}
	}
	void saveFile() {
		saveFile(root);
	
	}
	void count() {
		cout << endl << "Total Tickers : " << count(root) << endl;
	}
};