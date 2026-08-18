#pragma once

struct TreeNode {
    int key;             // 값 하나
    TreeNode* left;      // 왼쪽 자식 (나보다 작은 값들)
    TreeNode* right;     // 오른쪽 자식 (나보다 큰 값들)

    TreeNode(int k)
    {
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    TreeNode* root;
    TreeNode* insertHelper(TreeNode* node, int key);
    bool searchHelper(TreeNode* node, int key);
    void inorderHelper(TreeNode* node);
    void preorderHelper(TreeNode* node);
    void postorderHelper(TreeNode* node);
    void destroyHelper(TreeNode* node);

public:
    BST();
    ~BST();
    void insert(int key);
    bool search(int key);
    void remove(int key);
    void inorder();
    void preorder();
    void postorder();
    void levelorder();
};