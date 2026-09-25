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
    void destroyHelper(BTreeNode* node);
    bool searchHelper(BTreeNode* node, int key);
    void insertHelper(BTreeNode* node, int key);
    void splitChild(BTreeNode* parent, size_t i);

public:
    BTree(int order);      // 차수를 받아서 생성
    ~BTree();
    bool search(int key);
    void insert(int key);
};

///////////////////////////////////////////////////////////