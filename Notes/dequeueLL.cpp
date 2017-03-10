// DEQUEUE IN A LINKED LIST

node* Queue::dequeue() {
    node* del;

    if (head == NULL) { //check if the queue is empty
        return NULL;
    } else {
        del = head;
        head = head->next;
    }

    return del;

}//end dequeue
