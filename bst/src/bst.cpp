// bst.cpp
#include <iostream>
#include "../include/bst.hpp"

//////////////////////////////////////////////////////////////
BST::BST()
{
    root = nullptr;
}

//////////////////////////////////////////////////////////////
BST::~BST()
{
    // TODO: 모든 노드 해제 (후위 순회 배운 뒤 구현)
}

//////////////////////////////////////////////////////////////
void BST::insert(int key)
{
    root = insertHelper(root, key);
}

//////////////////////////////////////////////////////////////
TreeNode* BST::insertHelper(TreeNode* node, int key)
{
    if (node == nullptr)
        return new TreeNode(key);

    if (key < node->key)
        node->left = insertHelper(node->left, key);
    else if (key > node->key)
        node->right = insertHelper(node->right, key);

    return node;
}
//////////////////////////////////////////////////////////////
bool BST::search(int key)
{
    return searchHelper(root, key);
}

//////////////////////////////////////////////////////////////
bool BST::searchHelper(TreeNode* node, int key)
{
    if (node == nullptr)
        return false;
    else if (node->key == key)
        return true;
    else if (node->key > key)
        return searchHelper(node->left, key);
    else
        return searchHelper(node->right, key);
}

//////////////////////////////////////////////////////////////
void BST::inorder()
{
    inorderHelper(root);
}

//////////////////////////////////////////////////////////////
void BST::inorderHelper(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    inorderHelper(node->left);
    std::cout << node->key << " ";
    inorderHelper(node->right);
}

//////////////////////////////////////////////////////////////
void BST::preorder()
{
    preorderHelper(root);
}

//////////////////////////////////////////////////////////////
void BST::preorderHelper(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    std::cout << node->key << " ";
    preorderHelper(node->left);
    preorderHelper(node->right);
}

//////////////////////////////////////////////////////////////
void BST::postorder()
{
    postorderHelper(root);
}

//////////////////////////////////////////////////////////////
void BST::postorderHelper(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    postorderHelper(node->left);
    postorderHelper(node->right);
    std::cout << node->key << " ";
}

//////////////////////////////////////////////////////////////