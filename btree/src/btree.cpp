// btree.cpp
#include "../include/btree.hpp"
#include <iostream>

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

    if (isOverflow(root))
    {
        BTreeNode* node = new BTreeNode(false);
        node->children.push_back(root);
        root = node;
        splitChild(root, 0);
    }
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
        if (isOverflow(node->children[i]))
        {
            splitChild(node, i);
        }
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

    parent->keys.insert(parent->keys.begin() + i, midKey);

    parent->children.insert(parent->children.begin() + i+1, right);
}

///////////////////////////////////////////////////////////
bool BTree::isOverflow(BTreeNode* node)
{
    return node->keys.size() > (size_t)(order - 1);
}

///////////////////////////////////////////////////////////
void BTree::print()
{
    printHelper(root, 0);
}

///////////////////////////////////////////////////////////
void BTree::printHelper(BTreeNode* node, int depth)
{
    for (int d = 0; d < depth; d++)
    {
        std::cout << "    ";
    }

    std::cout << "[";
    for (size_t j = 0; j < node->keys.size(); j++)
    {
        std::cout << node->keys[j];
        if (j + 1 < node->keys.size())
        {
            std::cout << "|";
        }
    }
    std::cout << "]" << std::endl;

    for (BTreeNode* child : node->children)
    {
        printHelper(child, depth + 1);
    }
}