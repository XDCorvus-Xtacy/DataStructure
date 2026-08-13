// bst.cpp
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