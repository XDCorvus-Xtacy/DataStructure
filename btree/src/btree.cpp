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
    // ① 넘친 자식을 가져온다
    BTreeNode* child = parent->children[i];

    // ② 가운데 위치와 가운데 키를 구한다
    //    (midKey는 나중에 부모에 넣어야 하니 미리 저장!)
    size_t mid = child->keys.size() / 2;
    int midKey = child->keys[mid];

    // ③ 오른쪽 조각이 될 새 노드를 만든다
    //    힌트: isLeaf는 child와 같아야 해요. 왜일까요? 🤔
    BTreeNode* right = new BTreeNode(child->isLeaf);

    // ④ mid 다음 키들을 새 노드로 복사
    //    힌트: for (size_t j = mid + 1; j < child->keys.size(); j++)
    //          → right->keys.push_back(...)
    for (size_t j = mid + 1; j < child->keys.size(); j++)
    {
        right->keys.push_back(child->keys[j]);
    }

    // ⑤ 내부 노드면 자식들도 복사
    //    힌트: if (!child->isLeaf) { mid+1부터 끝까지 children 복사 }
    if (!child->isLeaf)
    {
        for (size_t j = mid + 1; j < child->children.size(); j++)
        {
            right->children.push_back(child->children[j]);
        }
    }
}

///////////////////////////////////////////////////////////
