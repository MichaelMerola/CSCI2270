// DELETES NODE IN ARRAY BASED ON INDEX

node * DeleteNode(node *head, int target) {
    node *temp;
    temp = head;
    int counter = 0;
    node *left;

    bool found = false; //search flag
    while (found != true) {
        if (counter == target) {
            left->next = temp->next;
            if (temp == head)
                head = left;

            found = true;
        }
        else {
            left = temp;
            temp = temp->next;
            counter++;
        }
    }//end while

    delete temp;
    return head;
}
