Node* search(Node* root, int value) {
    //iterative solution

    Node* temp = root;
    while (temp != NULL) {
        if (temp->key > value) {
            temp = temp->left;
        }
        else if (temp->key < value) {
            temp = temp->right;
        }
        else {
            return temp;
        }
    }

    return NULL;
}

Node* search(node* temp, int value) { //recursive solution

    if (value < temp->key && temp->left != NULL) {
        return search(temp->left, value);
    }
    if (temp->key == value) {
        return temp;
    }
    if (value > temp->key && temp->right != NULL){
        return search(temp->right, value);
    }
    return NULL;
}//end treeSearch
