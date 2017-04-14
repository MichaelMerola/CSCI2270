int min(TreeNode *node) {
  while (node->right != NULL) {
        node = node->right;
    }
    return node->key;
}

int max(TreeNode *node) {
  while (node->right != NULL) {
        node = node->right;
    }
    return node->key;
}
bool isBST(TreeNode *node) {
    if (node == NULL)
        return true;

    if (node->right != NULL && min(node->right) < node->key)
        return false;

    if (node->left != NULL && max(node->left) > node->key)
        return false;

    if ((!isBST(node->left)) || (!isBST(node->right)))
        return false;

    return true;
}
