// DELETES ALL TARGETS IN AN ARRAY

node * DeleteNode(node *head, int target) {
    node *temp;
    temp = head;


    if (head->value == target) { //check if head is target
        temp = head;
        head = head->next;
    }
    else {
        node *left = head;
        temp = head->next;
        //bool found = false; //search flag
        while (temp != NULL) {
            if (temp->value == target) {
                left->next = temp->next;
                temp = temp->next;
            }
            else {
                left = temp;
                temp = temp->next;
            }
        }
    }//end else

    delete temp;
    return head;
}
