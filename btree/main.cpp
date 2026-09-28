// main.cpp
#include <iostream>
#include "include/btree.hpp"

int main()
{
    BTree tree(3);

    int keys[] = {10, 20, 30, 40, 50, 60, 70};
    for (int k : keys)
    {
        tree.insert(k);
        std::cout << "--- insert " << k << " ---" << std::endl;
        tree.print();
    }

    std::cout << "search(50): " << tree.search(50) << std::endl;
    std::cout << "search(55): " << tree.search(55) << std::endl;
    return 0;
}