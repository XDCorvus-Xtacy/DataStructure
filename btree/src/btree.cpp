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
void BTree::splitChild(BTreeNode* parent, size_t i)
{
    BTreeNode* child = parent->children[i];

    size_t mid = child->keys.size() / 2;
    int midKey = child->keys[mid];

    BTreeNode* right = new BTreeNode(child->isLeaf);

    for (size_t j = mid + 1; j < child->keys.size(); j++)
    {
        right->keys.push_back(child->keys[j]);
    }

    if (!child->isLeaf)
    {
        for (size_t j = mid + 1; j < child->children.size(); j++)
        {
            right->children.push_back(child->children[j]);
        }
    }

    child->keys.resize(mid);

    if (!child->isLeaf)
    {
        child->children.resize(mid+1);
    }

    parent->keys.insert(parent->keys.begin() + i, midKey)

    parent->children.insert(parent->children.begin() + i+1, right)
}

///////////////////////////////////////////////////////////
