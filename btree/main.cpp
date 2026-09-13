// main.cpp
#include <iostream>
#include "include/btree.hpp"

int main()
{
    BTree tree(3);    // 차수 3짜리 트리 생성
    
    std::cout << tree.search(10) << std::endl;   // 0 (false) 나와야 함
    return 0;
}