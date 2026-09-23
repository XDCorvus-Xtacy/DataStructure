// btree.cpp
#include "../include/btree.hpp"

///////////////////////////////////////////////////////////
BTree::BTree(int order)
{
    this->order = order;
    root = new BTreeNode(true);
}

///////////////////////////////////////////////////////////
BTree::~BTree()
{
    destroyHelper(root);
}

///////////////////////////////////////////////////////////
void BTree::destroyHelper(BTreeNode* node)
{
    if (node == nullptr)
        return;

    for (BTreeNode* child : node->children)
    {
        destroyHelper(child);
    }

    delete node;
}

///////////////////////////////////////////////////////////
bool BTree::search(int key)
{
    return searchHelper(root, key);
}

///////////////////////////////////////////////////////////
bool BTree::searchHelper(BTreeNode* node, int key)
{
    size_t i = 0;
    while (i < node->keys.size() && key > node->keys[i])
        i++;

    if (i < node->keys.size() && node->keys[i] == key)
        return true;

    if (node->isLeaf)
        return false;

    return searchHelper(node->children[i], key);
}

///////////////////////////////////////////////////////////
void BTree::insert(int key)
{
    insertHelper(root, key);
}

///////////////////////////////////////////////////////////
void BTree::insertHelper(BTreeNode* node, int key)
{
    size_t i = 0;
    while (i < node->keys.size() && key > node->keys[i])
        i++;

    if (node->isLeaf)
    {
        node->keys.insert(node->keys.begin() + i, key);
    }
    else
    {
        insertHelper(node->children[i], key);
    }
}

///////////////////////////////////////////////////////////
