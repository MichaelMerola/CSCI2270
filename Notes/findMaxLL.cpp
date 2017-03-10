// FINDS MAXIMUM VALUE IN A LINKED LIST

void findMax() {
    int max = 0;
    Node *temp;
    temp = head;

    while (temp != NULL) {
        if (temp->key >= max) {
            max = temp->key;
        }
        temp = temp->next;
    }

    cout << max << endl;
}
