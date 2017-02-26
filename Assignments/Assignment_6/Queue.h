#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

using namespace std;

class Queue
{
    public:
        Queue(int); //constructor that takes an int
        ~Queue();
        //circular queue methods
        void enqueue(string);
        void enqSent(string);
        void dequeue(); //should send through network, call transmit msg
        void printQueue();
        bool qIsFull(); //send when full
        bool qIsEmpty(); //send when empty

    protected:
    private:
        int qCurrentSize;
        int qMaxSize;
        int head;
        int tail;
        int qCount;
        string *qArray;
};

#endif // QUEUE_H
