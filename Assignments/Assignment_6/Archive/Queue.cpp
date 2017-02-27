#include "Queue.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

Queue::Queue (int qs) {

    qMaxSize = qs;
    qArray = new string[qMaxSize];
    qCurrentSize = 0;
    head = 0;
    tail = 0;

}//end constructor

Queue::~Queue () {}

void Queue::enqueue(string word) {

    if (!qIsFull()) { //check if queue is full
        qArray[tail] = word;
        qCurrentSize++;
        if (tail == qMaxSize-1) { // check if tail is at end of array
            tail = 0; //reset tail to first position
        } else {
            tail++; //move tail to next empty spot
        }

        cout << "E: " << word << endl;
        cout << "H: " << head << endl;
        cout << "T: " << tail << endl;

    } else {
        cout << "Queue is full." << endl;
    }

}//end enqueue

void Queue::dequeue() {
    string del;

    if (!qIsEmpty()) { //check if the queue is empty
        del = qArray[head];
        qArray[head] = "";
        qCurrentSize--;
        if (head == qMaxSize-1) { //check if head is at end of array
            head = 0; //reset head to first position
        } else {
            head++; //move head to nex position
        }

        cout << "H: " << head << endl;
        cout << "T: " << tail << endl;
        cout << "word: " << del << endl;

    } else {
        cout << "Queue is empty." << endl;
    }

}//end dequeue

void Queue::enqSent(string sent) {

    stringstream ss(sent);
    string word;

    while (getline(ss, word, ' ')) { //check through each element (word) in the sentence

        enqueue(word);

    }//end while

}//end enqSent

void Queue::printQueue() {

    if (!qIsEmpty()) {

        /*if (qIsFull()) { //check if queue is full in case head and tail are at same index
            for (int i = 0; i < qMaxSize; i++) {
                cout << i << ": " << qArray[i] << endl;
            }//end for

        } else if (head < tail) { //check if head comes before tail
            for (int i = head; i < tail; i++) {
                cout << i << ": " << qArray[i] << endl;
            }//end for

        } else if (tail < head) { //check if tail comes before head
            for (int i = tail; i <= head; i++) {
                cout << i << ": " << qArray[i] << endl;
            }//end for

        }//end if */

        for (int i = head; i < qMaxSize; i++) {
            if (qArray[i] != "") { //check if spot in array is empty
                cout << i << ": " << qArray[i] << endl;
            }
        }//end for
        for (int j = 0; j < head; j++) {
            if (qArray[j] != "") { //check if spot in array is empty
                cout << j << ": " << qArray[j] << endl;
            }
        }

    } else {
        cout << "Empty" << endl;
    }

}//end printQueue

bool Queue::qIsFull() {

    if (qCurrentSize == qMaxSize) {
        return true; //queue is full
    }
    else {
        return false;
    }

}//end isFull

bool Queue::qIsEmpty() {

    if (qCurrentSize == 0) {
        return true; //queue is empty
    }
    else {
        return false;
    }

}//end isEmpty
