// DELETES ALL TARGET VALUES IN AN ARRAY

node * DeleteNode(node *head, int target) {
    node *temp;
    temp = head;

    node *left = head;
    //if deleting single node, create a search flag

    while (temp != NULL) {
        if (temp->value == target) {
            if (temp == head) {  //check if head is target
                head = head->next;
            }
            left->next = temp->next;
            temp = temp->next;
        }
        else {
            left = temp;
            temp = temp->next;
        }
    }

    delete temp;
    return head;
}
