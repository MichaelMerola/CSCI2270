void doubleTree(TreeNode *node) {

    TreeNode *old = new TreeNode();
    TreeNode *add = new TreeNode();

    if (node == NULL)
        return;

    doubleTree(node->left);
    doubleTree(node->right);

    old = node->left;
    add->key = node->key;

    node->left = add;
    node->left->left = old;

}
