// BUILDS A BST FROM A GIVEN ARRAY

int addNode(int value, Node *temp){
    if(value > temp -> key && temp -> right != NULL){
        addNode(value, temp -> right);
        return 0;
    }
    else if(value < temp-> key && temp-> left != NULL){
        addNode(value, temp-> left);
        return 0;
    }
    Node *n = new Node(temp, NULL, NULL);
    n->key = value;

    if(value < temp-> key){
        temp->left = n;
        cout<<"node: "<< n -> key<<" left child of: "<<temp -> key<<endl;
    }else if(value > temp -> key){
        temp->right = n;
        cout<<"node: "<< n -> key<<" right child of: "<<temp-> key<<endl;
    }

    return 0;
}

Node *build(int a[], int size){
    root = new Node(NULL, NULL, NULL);
    root -> key = a[0];
    cout<<"root: "<<root->key<<" parent: 0"<<endl;

    for(int i = 1; i < size; i++){
        addNode(a[i], root);
    }
    return root;
}
