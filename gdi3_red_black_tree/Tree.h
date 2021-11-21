
/**
* Änderung von key int Array[3] zu key int.
*/

#ifndef REDBLACK_TREE_H
#define REDBLACK_TREE_H

#include <string>
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
    Node* Node;
    int index; // Index des gefundenen Elements
    bool success;
    int comparisons;
} Result;

class RedBlackTree
{
private:
    Node* root;

public:
    RedBlackTree(int key, std::string value) {
        root = new Node();
        root->key = key;
        root->value = value;
    };

    void insertKey(int key, std::string value) {
        // Allocate memory for new node
        Node* z = new Node();
        z->key = key;
        z->value = value;
        z->left = z->right = z->parent = NULL;

        //if root is null make z as root
        if (root == NULL)
        {
            z->isRed = 0;
            (root) = z;
        }
        else
        {
            struct Node* y = NULL;
            struct Node* x = (root);

            // Follow standard BST insert steps to first insert the node
            while (x != NULL)
            {
                y = x;
                if (z->key < x->key)
                    x = x->left;
                else
                    x = x->right;
            }
            z->parent = y;
            if (z->key > y->key)
                y->right = z;
            else
                y->left = z;
            z->isRed = 1;

            // call insertFixUp to fix reb-black tree's property if it
            // is voilated due to insertion.
            fixInsert(z);
        }
    };
    Result searchKey(int key);
    void rotateLeft(Node* x)
    {
        if (!x || !x->right)
            return;
        //y stored pointer of right child of x
        struct Node* y = x->right;

        //store y's left subtree's pointer as x's right child
        x->right = y->left;

        //update parent pointer of x's right
        if (x->right != NULL)
            x->right->parent = x;

        //update y's parent pointer
        y->parent = x->parent;

        // if x's parent is null make y as root of tree
        if (x->parent == NULL)
            root = y;

        // store y at the place of x
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        // make x as left child of y
        y->left = x;

        //update parent pointer of x
        x->parent = y;
    };
    void rotateRight(Node* y) {
        if (!y || !y->left)
            return;
        struct Node* x = y->left;
        y->left = x->right;
        if (x->right != NULL)
            x->right->parent = y;
        x->parent = y->parent;
        if (x->parent == NULL)
            (root) = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;

    };
    void fixInsert(Node* z) {
        // iterate until z is not the root and z's parent color is red
        while (z != root && z != (root)->left && z != (root)->right && z->parent->isRed == 1)
        {
            struct Node* y;

            // Find uncle and store uncle in y
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
                y = z->parent->parent->right;
            else
                y = z->parent->parent->left;

            // If uncle is RED, do following
            // (i)  Change color of parent and uncle as BLACK
            // (ii) Change color of grandparent as RED
            // (iii) Move z to grandparent
            if (!y)
                z = z->parent->parent;
            else if (y->isRed == 1)
            {
                y->isRed = 0;
                z->parent->isRed = 0;
                z->parent->parent->isRed = 1;
                z = z->parent->parent;
            }

            // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
            else
            {
                // Left-Left (LL) case, do following
                // (i)  Swap color of parent and grandparent
                // (ii) Right Rotate Grandparent
                if (z->parent == z->parent->parent->left &&
                    z == z->parent->left)
                {
                    char ch = z->parent->isRed;
                    z->parent->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateRight( z->parent->parent);
                }

                // Left-Right (LR) case, do following
                // (i)  Swap color of current node  and grandparent
                // (ii) Left Rotate Parent
                // (iii) Right Rotate Grand Parent
                if (z->parent && z->parent->parent && z->parent == z->parent->parent->left &&                    z == z->parent->right)
                {
                    char ch = z->isRed;
                    z->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateLeft( z->parent);
                    rotateRight(z->parent->parent);
                }

                // Right-Right (RR) case, do following
                // (i)  Swap color of parent and grandparent
                // (ii) Left Rotate Grandparent
                if (z->parent && z->parent->parent &&
                    z->parent == z->parent->parent->right &&
                    z == z->parent->right)
                {
                    char ch = z->parent->isRed;
                    z->parent->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateLeft( z->parent->parent);
                }

                // Right-Left (RL) case, do following
                // (i)  Swap color of current node  and grandparent
                // (ii) Right Rotate Parent
                // (iii) Left Rotate Grand Parent
                if (z->parent && z->parent->parent && z->parent == z->parent->parent->right &&
                    z == z->parent->left)
                {
                    char ch = z->isRed;
                    z->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateRight( z->parent);
                    rotateLeft( z->parent->parent);
                }
            }
        }
        root->isRed = 0; //keep root always black

    };
};

#endif // REDBLACK_TREE_H