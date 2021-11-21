// gdi3_red_black_tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
int main()
{
    RedBlackTree x = RedBlackTree();

    std::string meme = "text";
    Result res = x.insertKey(0, "ich bin root");
    std::cout << res.index << std::endl;
    Result res2 = x.insertKey(1, "bin rechts von root");
    std::cout << res2.index << std::endl;
    x.insertKey(-1, "bin links von root");


    std::cout << "Hello Worwldd!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
