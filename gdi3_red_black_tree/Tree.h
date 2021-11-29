
/**
* Änderung von key int Array[3] zu key int.
*/

#ifndef REDBLACK_TREE_H
#define REDBLACK_TREE_H

#include <string>
#include <cassert>
typedef struct Node
{
	int key;
	std::string value;
	bool isRed; //1(true) = schwarz, 0(false) = rot
	Node* left;
	Node* right;
	Node* parent;
} Node;

typedef struct Result
{
	Node* Node = nullptr;
	int index; // Index des gefundenen Elements 
	bool success = false; // useless since we don't have any criteria for an unsuccessful Result
	int comparisons = 0;
} Result;

class RedBlackTree
{
private:
	Node* root = nullptr;

	Node* searchTreeHelper(Node* node, int key, Result* res) {
		res->comparisons++;
		if (node == NULL || key == node->key) {
			return node;
		}

		if (key < node->key) {
			return searchTreeHelper(node->left, key, res);
		}
		return searchTreeHelper(node->right, key, res);
	}

	/*
	* Cormen et al P. 316
	*/
	void leftRotate(Node* x)
	{
		if (!x || !x->right)
			return;

		// y stored pointer to right child of testLeftRotation
		Node* y = x->right;

		// store y's left subtree's pointer as testLeftRotation's right child
		x->right = y->left;

		// update parent pointer of testLeftRotation's right
		if (x->right != NULL)
			x->right->parent = x;

		// update y's parent pointer
		y->parent = x->parent;

		// if testLeftRotation's parent points to null => make y as root of the tree
		if (x->parent == NULL) {
			root = y;
		}
		else if (x == x->parent->left) {
			// replace testLeftRotation with y
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		// set testLeftRotation as left child of y
		y->left = x;

		// update parent pointer of testLeftRotation
		x->parent = y;
	};

	void rightRotate(Node* y) {
		if (!y || !y->left)
			return;

		Node* x = y->left;
		y->left = x->right;

		if (x->right != NULL)
			x->right->parent = y;

		x->parent = y->parent;

		if (x->parent == NULL) {
			root = x;
		}
		else if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}

		x->right = y;
		y->parent = x;
	};

	/*
		See Cormen et al "Introduction to Algorithms"
		P. 318
	*/
	void insertFixup(Node* z) {

		// iterate till z is not the root and z's parent color is red
		// z->parent can be be dereferencing a null pointer according to my compiler but idk lol
		while (z->parent != nullptr && z->parent->isRed == 1)
		{
			Node* y;

			if (z->parent == z->parent->parent->left) {
				y = z->parent->parent->right;
				if (y && y->isRed == 1) {
					z->parent->isRed = 0;
					y->isRed = 0;
					z->parent->parent->isRed = 1;
					z = z->parent->parent;
				}
				else if (z == z->parent->right) {
					z = z->parent;
					leftRotate(z);
				}
				else {
					z->parent->isRed = 0;
					z->parent->parent->isRed = 1;
					rightRotate(z->parent->parent);
				}
			}
			else {

				y = z->parent->parent->left;

				if (y && y->isRed) {
					// case 4
					z->parent->isRed = 0;
					y->isRed = 0;
					z = z->parent->parent;
				}
				else if (z == z->parent->left) {
					z = z->parent;
					rightRotate(z);
				}
				else {
					z->parent->isRed = 0;
					z->parent->parent->isRed = 1;
					leftRotate(z->parent->parent);
				}
			}

		}
		root->isRed = 0; // root is always black
	};

public:
	RedBlackTree() {
	};

	static bool test() {
		// tests


		// ---
		// test rotations
		RedBlackTree testLeftRotation = RedBlackTree();
		testLeftRotation.insertKey(7, "bin root");
		testLeftRotation.insertKey(4, "bin links von root");
		testLeftRotation.insertKey(11, "bin rechts von root");
		testLeftRotation.insertKey(18, "bin rechts von 11");
		testLeftRotation.insertKey(9, "bin links von 11");
		testLeftRotation.insertKey(14, "bin links von 18");
		testLeftRotation.insertKey(19, "bin rechts von 18");


		// check if tree is correct. colors do not matter at this point since we are only testing rotations.
		assert(testLeftRotation.root->key == 7);
		assert(testLeftRotation.root->left->key == 4);
		assert(testLeftRotation.root->right->key == 11);
		assert(testLeftRotation.root->right->right->key == 18);
		assert(testLeftRotation.root->right->left->key == 9);
		assert(testLeftRotation.root->right->right->left->key == 14);
		assert(testLeftRotation.root->right->right->right->key == 19);

		// rotate left
		testLeftRotation.leftRotate(testLeftRotation.root->right);

		// check if right rotation is correct
		assert(testLeftRotation.root->key == 7);
		assert(testLeftRotation.root->left->key == 4);
		assert(testLeftRotation.root->right->left->key == 11);
		assert(testLeftRotation.root->right->key == 18);
		assert(testLeftRotation.root->right->left->left->key == 9);
		assert(testLeftRotation.root->right->left->right->key == 14);
		assert(testLeftRotation.root->right->right->key == 19);

		// ---
		// test rotate right on a new tree
		RedBlackTree testRightRotation = RedBlackTree();

		testRightRotation.insertKey(10, "bin root");
		testRightRotation.insertKey(5, "bin links von root");
		testRightRotation.insertKey(12, "bin rechts von root");
		testRightRotation.insertKey(2, "bin links von 5");
		testRightRotation.insertKey(8, "bin rechts von 5");
		testRightRotation.insertKey(6, "bin links von 8");
		testRightRotation.insertKey(9, "bin rechts von 9");

		// check if tree is correct. colors do not matter at this point since we are only testing rotations.
		assert(testRightRotation.root->key == 10);
		assert(testRightRotation.root->left->key == 5);
		assert(testRightRotation.root->right->key == 12);
		assert(testRightRotation.root->left->left->key == 2);
		assert(testRightRotation.root->left->right->key == 8);
		assert(testRightRotation.root->left->right->left->key == 6);
		assert(testRightRotation.root->left->right->right->key == 9);

		// rotate right
		testRightRotation.rightRotate(testRightRotation.root);

		// check if right rotation is correct
		assert(testRightRotation.root->right->key == 10);
		assert(testRightRotation.root->key == 5);
		assert(testRightRotation.root->right->right->key == 12);
		assert(testRightRotation.root->left->key == 2);
		assert(testRightRotation.root->right->left->key == 8);
		assert(testRightRotation.root->right->left->left->key == 6);
		assert(testRightRotation.root->right->left->right->key == 9);

		// create tree and test all axioms 
		RedBlackTree x = RedBlackTree();
		x.insertKey(11, "bin root");
		x.insertKey(2, "bin links von root");
		x.insertKey(14, "bin rechts von root");

		x.insertKey(1, "bin links von 2");
		x.insertKey(7, "bin rechts von 2");


		x.insertKey(15, "bin rechts von 14");

		x.insertKey(5, "bin links von 7");
		x.insertKey(8, "bin rechts von 7");

		x.insertKey(4, "bin links von 5");
		std::cout << "Is tree valid: " << x.isTreeValid() << std::endl;
		return true;
	}

private: bool validation(Node* x, int* leftCounter, int* rightCounter) {
	// funny recursive function 
	// 1
	assert(x);	

	// 2
	assert(root);

	// 3
	if (x->left == nullptr && x->right == nullptr && x->isRed == 0)
		assert(x->isRed == 0);

	// 4 
	if (x->isRed) {
		if (x->left) {
			assert(x->left->isRed == 0);
		}
		if (x->right) {
			assert(x->right->isRed == 0);
		}
	}

	// 5
	if (!x->isRed && x->left)
		*leftCounter = *leftCounter + 1;

	if (!x->isRed && x->right)
		*rightCounter = *rightCounter + 1;


	// go down to the decending nodes
	if (x->left)
		validation(x->left, leftCounter, rightCounter);
	if (x->right)
		validation(x->right, leftCounter, rightCounter);

	return true;
}

private: bool isTreeValid() {
	/*
		1. each node is either red or black. - always true since we set it in insertKey right at the beginning
		2. the root is black.
		3. each leaf (nil) is black.
		4. if a node is red, then its two children are black.
		5. for each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

	*/


	// 1 & 2 & 3 & 4 & 5
	int leftCounter, rightCounter = 0;
	leftCounter = 0;
	rightCounter = 0;
	validation(root, &leftCounter, &rightCounter);

	// if the leftCounter and rightCounter are the same, we have a correct rule #5
	assert(leftCounter == rightCounter);
	// std::cout << "left: " << leftCounter << " right: " << rightCounter << std::endl;

	return true;
}

public:    Result insertKey(int key, std::string value) {
	Result res = Result();
	res.comparisons = 0;

	Node* y = NULL;
	Node* x = root;

	Node* z = new Node();
	z->key = key;
	z->value = value;
	z->isRed = 0;
	z->left = z->right = z->parent = nullptr;

	while (x != NULL) {
		y = x;
		res.comparisons++;
		if (z->key < x->key) {
			x = x->left;
		}
		else {
			x = x->right;
		}
	}

	z->parent = y;

	res.comparisons++;
	if (y == nullptr) {
		root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else {
		y->right = z;
	}

	z->left = nullptr;
	z->right = nullptr;
	z->isRed = 1;
	insertFixup(z);

	return res;

	/*
	Result res = Result();
	res.comparisons = 0;

	Node* z = new Node();
	z->key = key;
	z->value = value;
	z->isRed = 1;
	z->left = z->right = z->parent = nullptr;

	// if root is null set our new node as root
	if (root == nullptr)
	{
		z->isRed = 0;
		root = z;
		res.success = true;
		res.index = z->key;
		res.comparisons++;
		return res;
	}
	else
	{
		Node* y = nullptr;
		Node* x = root;

		// binary search tree insert to first insert the node
		while (x != nullptr)
		{
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
			res.comparisons++;
		}
		z->parent = y;
		if (y == nullptr) {
			root = z;
		}
		else if (z->key < y->key) {
			y->left = z;
		}
		else {
			y->right = z;
		}
		z->isRed = 1;
		res.comparisons++;

		// call insertFixup to fix RB tree property if it is voilated in newest insertion.
		insertFixup(z);
	}

	res.success = true;
	res.index = z->key;
	return res;
	*/
};


	  Result searchKey(int key) {
		  Result* res = new Result();
		  res->comparisons = 0;
		  res->index = searchTreeHelper(this->root, key, res)->key;
		  return *res;
	  };





};

#endif // REDBLACK_TREE_H