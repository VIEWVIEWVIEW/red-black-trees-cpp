#include <iostream>
#include "Tree.h"

// Beispiel ist ein Beispiel zur Benutzung der Library.
void Beispiel() {
    RedBlackTree exampleTree = RedBlackTree();
    exampleTree.insertKey(7, "bin root");
    exampleTree.insertKey(4, "bin links von root");
    exampleTree.insertKey(11, "bin rechts von root");

    Result res = exampleTree.searchKey(11);
    std::cout << "Success " << res.success << std::endl;
    std::cout << "Comparisons " << res.comparisons << std::endl;
    Node* node = res.Node;
}

int main()
{
    RedBlackTree::test();

    Beispiel();

    return 0;
}
