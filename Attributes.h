#pragma once
#include "includes.h"
struct node {
	int key;
	struct node* left;
	struct node* right;
	int height;
	int count;
	//char* ticker;
	list l;

};

// A utility function to get maximum of two integers 
class avlTree {
public:
	avlTree() {

	}
	~avlTree() {
	}
	// A utility function to get height of the tree 
	int height(struct node* N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}

	// A utility function to get maximum of two integers 
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}

	/* Helper function that allocates a new node with the given key and
	NULL left and right pointers. */
	struct node* newNode(char* str, int key_)
	{
		struct node* node = (struct node*)
			new struct node;


		node->left = NULL;
		node->right = NULL;
		node->key = key_;
		node->height = 1; // new node is initially added at leaf 
		node->count = 1;
		//node->ticker = str;
		node->l.insertathead(str);
		return (node);
	}

	// A utility function to right rotate subtree rooted with y 
	// See the diagram given above. 
	struct node* rightRotate(struct node* y)
	{
		struct node* x = y->left;
		struct node* T2 = x->right;

		// Perform rotation 
		x->right = y;
		y->left = T2;

		// Update heights 
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		// Return new root 
		return x;
	}

	// A utility function to left rotate subtree rooted with x 
	// See the diagram given above. 
	struct node* leftRotate(struct node* x)
	{
		struct node* y = x->right;
		struct node* T2 = y->left;

		// Perform rotation 
		y->left = x;
		x->right = T2;

		// Update heights 
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		// Return new root 
		return y;
	}

	// Get Balance factor of node N 
	int getBalance(struct node* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}

	struct node* insert(struct node* node, char* str, int key_)
	{

		/* 1.  Perform the normal BST rotation */
		if (node == NULL)
			return (newNode(str, key_));
		
		// If key already exists in BST, increment count and return 
		if (key_ == node->key ) {

			node->l.insertathead(str);

			
				return node;
		}

		/* Otherwise, recur down the tree */
		if (key_ < node->key)
			node->left = insert(node->left, str, key_);
		else
			node->right = insert(node->right, str, key_);

		/* 2. Update height of this ancestor node */
		node->height = max(height(node->left), height(node->right)) + 1;

		/* 3. Get the balance factor of this ancestor node to check whether
		this node became unbalanced */
		int balance = getBalance(node);

		// If this node becomes unbalanced, then there are 4 cases 

		// Left Left Case 
		if (balance > 1 && key_ < node->left->key)
			return rightRotate(node);

		// Right Right Case 
		if (balance < -1 && key_ > node->right->key)
			return leftRotate(node);

		// Left Right Case 
		if (balance > 1 && key_ > node->left->key) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// Right Left Case 
		if (balance < -1 && key_ < node->right->key) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		/* return the (unchanged) node pointer */
		return node;
	}

	void Inrange(node* root, int up, int low)
	{
		/* base case */
		if (NULL == root)
			return;


		if (up < root->key)
			Inrange(root->left, up, low);


		if (up <= root->key && low >= root->key)
		{
			printf("\t\tTicker :");
			root->l.displaylist();
			printf("\t\tValue : %d\n", root->key);
		}

		if (low > root->key)
			Inrange(root->right, up, low);
	}

	/* Given a non-empty binary search tree, return the node with minimum
	key value found in that tree. Note that the entire tree does not
	need to be searched. */
	struct node* minValueNode(struct node* node)
	{
		struct node* current = node;

		/* loop down to find the leftmost leaf */
		while (current->left != NULL)
			current = current->left;

		return current;
	}


	struct node* search_key(struct node* root, int key)
	{
		// Base Cases: root is null or key is present at root 
		if (root == NULL ||root->key == key)
			return root;

		// Key is greater than root's key 
		if (root->key < key)
			return search_key(root->right, key);

		// Key is smaller than root's key 
		return search_key(root->left, key);
	}



	// A utility function to print preorder traversal of the tree. 
	// The function also prints height of every node 
	void preOrder(struct node* root)
	{
		if (root != NULL) {
			/*	for (int i = 0; i < root->l.countlist(); i++) {
					cout << root->l.atindex(i);
				}*/
			root->l.displaylist();
			printf("%d  ", root->key);
			preOrder(root->left);
			preOrder(root->right);
		}
	}

	struct node * deleteNode(struct node * root, int key)
	{

		// STEP 1: PERFORM STANDARD BST DELETE  
		if (root == NULL)
			return root;

		// If the key to be deleted is smaller  
		// than the root's key, then it lies 
		// in left subtree  
		if (key < root->key)
			root->left = deleteNode(root->left, key);

		// If the key to be deleted is greater  
		// than the root's key, then it lies  
		// in right subtree  
		else if (key > root->key)
			root->right = deleteNode(root->right, key);

		// if key is same as root's key, then  
		// This is the node to be deleted  
		else
		{
			// node with only one child or no child  
			if ((root->left == NULL) ||
				(root->right == NULL))
			{
				struct node* temp = (struct node*)
					new struct node;

				 temp = root->left ?
					root->left :
					root->right;

				// No child case  
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else // One child case  
					*root = *temp; // Copy the contents of  
								   // the non-empty child  
				delete temp;
			}
			else
			{
				// node with two children: Get the inorder  
				// successor (smallest in the right subtree)  
				struct node* temp = (struct node*)
					new struct node;
				 temp = minValueNode(root->right);

				// Copy the inorder successor's  
				// data to this node  
				root->key = temp->key;

				// Delete the inorder successor  
				root->right = deleteNode(root->right,
					temp->key);
			}
		}

		// If the tree had only one node 
		// then return  
		if (root == NULL)
			return root;

		// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
		root->height = 1 + max(height(root->left),
			height(root->right));

		// STEP 3: GET THE BALANCE FACTOR OF  
		// THIS NODE (to check whether this  
		// node became unbalanced)  
		int balance = getBalance(root);

		// If this node becomes unbalanced,  
		// then there are 4 cases  

		// Left Left Case  
		if (balance > 1 &&
			getBalance(root->left) >= 0)
			return rightRotate(root);

		// Left Right Case  
		if (balance > 1 &&
			getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// Right Right Case  
		if (balance < -1 &&
			getBalance(root->right) <= 0)
			return leftRotate(root);

		// Right Left Case  
		if (balance < -1 &&
			getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}
	// A function to find k'th largest element in a given tree. 
	void kthLargestUtil(node* root, int k, int& c,string str)
	{
		// Base cases, the second condition is important to 
		// avoid unnecessary recursive calls 
		if (root == NULL || c >= k)
			return;

		// Follow reverse inorder traversal so that the 
		// largest element is visited first 
		kthLargestUtil(root->right, k, c,str);

		// Increment count of visited nodes 
		c++;

		// If c becomes k now, then this is the k'th largest  
		if (c == k)
		{
			printf("%d Ticker : ", k);
			root->l.displaylist();
			cout << str << " : " << root->key << endl;
			return;
		}

		// Recur for left subtree 
		kthLargestUtil(root->left, k, c,str);
	}

	// Function to find k'th largest element 
	void kthLargest(node* root, int k,string str)
	{
		// Initialize count of nodes visited as 0 
		int c = 0;

		// Note that c is passed by reference 
		kthLargestUtil(root, k, c,str);
	}


	void nlargest(int n, node* root,string str) {
		for (int i = 1; i <= n; i++)
			kthLargest(root, i,str);
	}



	void kthsmallestUtil(node* root, int k, int& c,string str)
	{
		// Base cases, the second condition is important to 
		// avoid unnecessary recursive calls 
		if (root == NULL || c >= k)
			return;

		// Follow reverse inorder traversal so that the 
		// smallest element is visited first 
		kthsmallestUtil(root->left, k, c,str);

		// Increment count of visited nodes 
		c++;

		// If c becomes k now, then this is the k'th smallest  
		if (c == k)
		{
			printf("%d Ticker : ", k);
			root->l.displaylist();
			cout << str << " : " << root->key << endl;
			return;
		}

		// Recur for left subtree 
		kthsmallestUtil(root->right, k, c, str);
	}

	// Function to find k'th smallest element 
	void kthsmallest(node* root, int k,string str)
	{
		// Initialize count of nodes visited as 0 
		int c = 0;

		// Note that c is passed by reference 
		kthsmallestUtil(root, k, c,str);
	}


	void nsmallest(int n, node* root,string str) {
		for (int i = 1; i <= n; i++)
			kthsmallest(root, i,str);
	}

};