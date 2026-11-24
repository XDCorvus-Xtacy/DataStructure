// bplustree.cpp
#include "../include/bplustree.hpp"
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
    // 1. 리프에 도착하면: 리프 안에 key가 있는지 확인
    if (node->isLeaf)
    {
        for (int k : node->keys)
        {
            if (k == key)
                return true;
        }
        return false;
    }

    // 2. 내부 노드: 이정표로 내려갈 자식 고르기
    //    작으면 왼쪽, 같거나 크면 오른쪽
    size_t i = 0;
    while (i < node->keys.size() && key >= node->keys[i])
        i++;

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

    size_t start;
    if (child->isLeaf)
    {
        start = mid;
    }
    else
    {
        start = mid + 1;
    }

    for (size_t j = start; j < child->keys.size(); j++)
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

    if (child->isLeaf)
    {
        right->next = child->next;
        child->next = right;
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

///////////////////////////////////////////////////////////
void BTree::printLeaves()
{
    BTreeNode* pTmp = root;

    while (pTmp->isLeaf != true)
    {
        pTmp = pTmp->children[0];
    }

    while (pTmp != nullptr)
    {
        std::cout << "[";
        for (size_t j = 0; j < pTmp->keys.size(); j++)
        {
            std::cout << pTmp->keys[j];
            if (j + 1 < pTmp->keys.size())
            {
                std::cout << "|";
            }
        }
        std::cout << "]" << std::endl;

        pTmp = pTmp->next;
    }
}

///////////////////////////////////////////////////////////
void BTree::rangeQuery(int low, int high)
{
    // 1. low가 있을 리프까지 내려가기 (search와 같은 규칙)
    BTreeNode* node = root;
    while (!node->isLeaf)
    {
        size_t i = 0;
        while (i < node->keys.size() && low >= node->keys[i])
            i++;
        node = node->children[i];
    }

    // 2. 리프를 따라 옆으로 걸으며 값 하나씩 확인
    while (node != nullptr)
    {
        for (int k : node->keys)
        {
            if (k > high)          // 끝 값을 넘으면 즉시 종료
            {
                std::cout << std::endl;
                return;
            }
            if (k >= low)          // 범위 안이면 출력
                std::cout << k << " ";
        }
        node = node->next;         // 다음 리프로
    }
    std::cout << std::endl;        // 마지막 리프까지 다 본 경우
}

///////////////////////////////////////////////////////////
