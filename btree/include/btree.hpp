// btree.hpp
#pragma once
#include <vector>

///////////////////////////////////////////////////////////
struct BTreeNode {
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool leaf) { isLeaf = leaf; }
};

///////////////////////////////////////////////////////////
class BTree {
private:
    BTreeNode* root;
    int order;

public:
    BTree(int order);      // 차수를 받아서 생성
    ~BTree();
    bool search(int key);  // 오늘/다음에 구현할 것
    void insert(int key);  // 나중에
};

///////////////////////////////////////////////////////////