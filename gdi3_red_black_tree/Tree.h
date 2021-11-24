
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
    // = KEY?
    // WTF?
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

public:
    RedBlackTree() {
    };

    Result insertKey(int key, std::string value) {
        Result res = Result();
        res.comparisons = 0;

        Node* z = new Node();
        z->key = key;
        z->value = value;
        z->left = z->right = z->parent = NULL;

        // if root is null set our new node as root
        if (root == NULL)
        {
            z->isRed = 0;
            root = z;
        }
        else
        {
            struct Node* y = NULL;
            struct Node* x = (root);

            // binary search tree insert to first insert the node
            while (x != NULL)
            {
                y = x;
                if (z->key < x->key)
                    x = x->left;
                else
                    x = x->right;
                res.comparisons++;
            }
            z->parent = y;
            if (z->key > y->key)
                y->right = z;
            else
                y->left = z;
            z->isRed = 1;
            res.comparisons++;

            // call fixInsert to fix RB tree property if it is voilated in newest insertion.
            fixInsert(z);
        }

        res.success = true; // useless for insert
        res.index = z->key;
        return res;
    };

    Result searchKey(int key) {
        Result * res = new Result();
        res->comparisons = 0;
        res->index = searchTreeHelper(this->root, key, res)->key;
        return *res; 
    };



    void rotateLeft(Node* x)
    {
        if (!x || !x->right)
            return;

        // y stored pointer to right child of x
        struct Node* y = x->right;

        // store y's left subtree's pointer as x's right child
        x->right = y->left;

        // update parent pointer of x's right
        if (x->right != NULL)
            x->right->parent = x;

        // update y's parent pointer
        y->parent = x->parent;

        // if x's parent is null make y as root of the tree
        if (x->parent == NULL)
            root = y;

        // store y at the place of x
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        // make x as left child of y
        y->left = x;

        // update parent pointer of x
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
        // iterate till z is not the root and z's parent color is red
        // z->parent can be be dereferencing a null pointer according to my compiler but idk lol
        while (z != root && z != root->left && z != root->right && z->parent->isRed == 1)
        {
            struct Node* y;

            // Find uncle and store uncle in y
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
                y = z->parent->parent->right;
            else
                y = z->parent->parent->left; // MSCVC: Dereferencing NULL pointer 'z->parent'. See line 130 for an earlier location where this can occur


            // If uncle is RED, do following
            // - Change color of parent and uncle as black
            // - Change color of grandparent as red
            // - Move z to grandparent
            if (!y)
                z = z->parent->parent;
            else if (y->isRed == 1)
            {
                y->isRed = 0;
                z->parent->isRed = 0;
                z->parent->parent->isRed = 1;
                z = z->parent->parent;
            }

            // Uncle is black, there are four cases (LL, LR, RL and RR)
            else
            {
                // LeftLeft (LL) case, do following
                // - swap color of parent and grandparent
                // - rotate to the right grandparent
                if (z->parent == z->parent->parent->left &&
                    z == z->parent->left)
                {
                    char ch = z->parent->isRed;
                    z->parent->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateRight( z->parent->parent);
                }

                // LeftRight (LR) case, do following
                // - swap color of current node and grandparent
                // - left rotate parent
                // - right rotate grand parent
                if (z->parent && z->parent->parent && z->parent == z->parent->parent->left && z == z->parent->right)
                {
                    char ch = z->isRed;
                    z->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateLeft( z->parent);
                    rotateRight(z->parent->parent);
                }

                // RightRight (RR) case, do following
                // - swap color of parent and grandparent
                // - left rotate grandparent
                if (z->parent && z->parent->parent &&
                    z->parent == z->parent->parent->right &&
                    z == z->parent->right)
                {
                    char ch = z->parent->isRed;
                    z->parent->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateLeft( z->parent->parent);
                }

                // RightLeft (RL) case, do following
                // - swap color of current node  and grandparent
                // - right Rotate Parent
                // - left Rotate Grand Parent
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
        root->isRed = 0; // root is always black

    };
};

#endif // REDBLACK_TREE_H