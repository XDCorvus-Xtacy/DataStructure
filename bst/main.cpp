#include <iostream>
#include "include/bst.hpp"

int main()
{
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);

    std::cout << "중위 순회: ";
    tree.inorder();
    std::cout << std::endl;

    std::cout << "전위 순회: ";
    tree.preorder();
    std::cout << std::endl;

    std::cout << "후위 순회: ";
    tree.postorder();
    std::cout << std::endl;

    return 0;
}