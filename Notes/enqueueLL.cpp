// ENQUEUE A NODE INTO A LINKED LIST

void Queue::enqueue(node *newNode) {

    if (head == NULL) {
        tail = newNode;
        head = tail;
        head->next = NULL;
        tail->next = NULL;
    }
    else if (tail->next == NULL) {
        tail->next = newNode;
        tail = tail->next;
    }

}
