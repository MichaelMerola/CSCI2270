int Path(TreeNode *node) {
        if (node == NULL) {
                return 0;
        }

        return 1 + max(Path(node->leftChild), Path(node->rightChild));
}

TreeNode* CheckHeightAndRotate(TreeNode *root) {
        bool finish = 0;
        bool left = 0;
        bool right = 0;

        TreeNode *temp = root;
        TreeNode *help = NULL;

        while (!finish) {
                temp = root;
                if (Path(root->leftChild) - Path(root->rightChild) > 1) {
                        right = 1;
                }

                else if (Path(root->rightChild) - Path(root->leftChild) > 1) {
                        left = 1;
                }

                if (left) {
                        help = temp->rightChild;
                        temp->rightChild = help->leftChild;

                        if  (help->leftChild != NULL) {
                                help->leftChild->parent = temp;
                        }

                        help->parent = temp->parent;

                        if (NULL == temp->parent) {
                                root = help;
                        }

                        else {
                                if (temp == temp->parent->leftChild) {
                                        temp->parent->leftChild = help;
                                }

                                else {
                                        temp->parent->rightChild = help;
                                }
                        }

                        help->leftChild = temp;
                        temp->parent = help;
                        left = 0;
                }

                if (right) {

                        help = temp->leftChild;
                        temp->leftChild = help->rightChild;

                        if (help->rightChild != NULL) {
                                help->rightChild->parent = temp;
                        }

                        help->parent = temp->parent;

                        if (NULL == temp->parent) {
                                root = help;
                        }

                        else if (temp == (temp->parent->leftChild)) {
                                temp->parent->leftChild = help;
                        }

                        else {
                                temp->parent->rightChild = help;
                        }

                        help->rightChild = temp;
                        temp->parent = help;
                        right = 0;
                }

                if (abs(Path(root->leftChild) - Path(root->rightChild)) <= 1) {
                        finish = 1;
                }
        }

        return root;
}
