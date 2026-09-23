// main.cpp
#include <iostream>
#include "include/btree.hpp"

int main()
{
    BTree tree(3);
    tree.insert(30);
    tree.insert(50);

    std::cout << tree.search(30) << std::endl;   // 1
    std::cout << tree.search(45) << std::endl;   // 0
    tree.insert(45);
    std::cout << tree.search(45) << std::endl;   // 1
    return 0;
}