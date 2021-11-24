// gdi3_red_black_tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
int main()
{
    RedBlackTree x = RedBlackTree();

    /*
    std::string meme = "text";
    Result res = x.insertKey(0, "ich bin root");
    std::cout << res.index << std::endl;
    Result res2 = x.insertKey(1, "bin rechts von root");
    std::cout << res2.index << std::endl;
    x.insertKey(-1, "bin links von root");
    */
    x.insertKey(13, "bin root");
    x.insertKey(8, "bin links von root und rot");
    x.insertKey(17, "bin rechts von root und rot");
    x.insertKey(1, "bin links von 8 und schwarz");
    x.insertKey(6, "bin rechts von 1 und bin rot");
    x.insertKey(11, "bin rechts von 8 und schwarz");
    x.insertKey(15, "bin links von 17 und schwarz");
    x.insertKey(25, "bin rechts von 17 und schwarz");
    x.insertKey(22, "bin links von 25 und rot");
    x.insertKey(27, "bin rechts von 25 und rot");

    Result res3 = x.searchKey(6);
    std::cout << "Hello Worwldd!\n";
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
