
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

    void leftRotate(Node* x)
    {
        if (!x || !x->right)
            return;

        // y stored pointer to right child of x
        struct Node* y = x->right;

        // store y's left subtree's pointer as x's right child
        x->right = y->left;

        // update parent pointer of x's right
        if (x->right != nullptr)
            x->right->parent = x;

        // update y's parent pointer
        y->parent = x->parent;

        // if x's parent points to null => make y as root of the tree
        if (x->parent == nullptr) {
            root = y;
        }
        else if (x == x->parent->left) {
            // replace x with y
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }
        // set x as left child of y
        y->left = x;

        // update parent pointer of x
        x->parent = y;
    };

    void rotateRight(Node* y) {
        if (!y || !y->left)
            return;

        struct Node* x = y->left;
        y->left = x->right;

        if (x->right != nullptr)
            x->right->parent = y;

        x->parent = y->parent;

        if (x->parent == nullptr) {
            (root) = x;
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
        P. 318 for more information plus this typescript implementation
        https://gist.github.com/hackwaly/7fdc89f1a0325a541f24#file-red_black_tree-ts-L122-L165
    */
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
                    bool ch = z->parent->isRed;
                    z->parent->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateRight(z->parent->parent);
                }

                // LeftRight (LR) case, do following
                // - swap color of current node and grandparent
                // - left rotate parent
                // - right rotate grand parent
                if (z->parent && z->parent->parent && z->parent == z->parent->parent->left && z == z->parent->right)
                {
                    bool ch = z->isRed;
                    z->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    leftRotate(z->parent);
                    rotateRight(z->parent->parent);
                }

                // RightRight (RR) case, do following
                // - swap color of parent and grandparent
                // - left rotate grandparent
                if (z->parent && z->parent->parent &&
                    z->parent == z->parent->parent->right &&
                    z == z->parent->right)
                {
                    bool ch = z->parent->isRed;
                    z->parent->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    leftRotate(z->parent->parent);
                }

                // RightLeft (RL) case, do following
                // - swap color of current node  and grandparent
                // - right Rotate Parent
                // - left Rotate Grand Parent
                if (z->parent && z->parent->parent && z->parent == z->parent->parent->right &&
                    z == z->parent->left)
                {
                    bool ch = z->isRed;
                    z->isRed = z->parent->parent->isRed;
                    z->parent->parent->isRed = ch;
                    rotateRight(z->parent);
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
        // create tree for testing
        RedBlackTree x = RedBlackTree();

        // 3
        x.insertKey(26, "bin root");
        x.insertKey(17, "bin links von root und rot");

        // 2
        x.insertKey(41, "bin rechts von root und schwarz");
        x.insertKey(21, "bin rechts von 17 und schwarz");
        x.insertKey(14, "bin links von 17 und schwarz");
        x.insertKey(30, "bin links von 41 und rot");

        // 1
        x.insertKey(47, "bin rechts von 41 und rot");
        x.insertKey(23, "bin rechts von 21 und schwarz");
        x.insertKey(19, "bin links von 21 und schwarz");
        x.insertKey(28, "bin links von 30 und schwarz");
        x.insertKey(38, "bin rechts von 30 und schwarz");
        x.insertKey(35, "bin links von 38 und rot");
        x.insertKey(39, "bin rechts von 38 und rot");
        x.insertKey(16, "bin rechts von 14 und schwarz");
        x.insertKey(15, "bin links von 16 und rot");
        x.insertKey(10, "bin links von 14 und rot");
        x.insertKey(12, "bin rechts von 10 und schwarz");
        x.insertKey(7, "bin links von 10 und schwarz");


        // tests
        // root node
        assert(x.root->parent == nullptr);
        assert(x.root->key == 26); 
        assert(x.root->isRed == 0);

        // 17
        assert(x.root->left->key == 17); 
        assert(x.root->left->isRed == 1);

        // 41
        assert(x.root->right->key == 41);
        assert(x.root->right->isRed == 0);

        // 14
        assert(x.root->left->left->key == 14);


        return true;
    }

    Result insertKey(int key, std::string value) {
        Result res = Result();
        res.comparisons = 0;

        Node* z = new Node();
        z->key = key;
        z->value = value;
        z->isRed = 0;
        z->left = z->right = z->parent = nullptr;

        // if root is null set our new node as root
        if (root == nullptr)
        {
            z->isRed = 0;
            root = z;
        }
        else
        {
            struct Node* y = nullptr;
            struct Node* x = root;

            // binary search tree insert to first insert the node
            while (x != nullptr)
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
            else if (z->key < y->key)
                y->left = z;
            else
                y->right = z;
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



    

};

#endif // REDBLACK_TREE_H