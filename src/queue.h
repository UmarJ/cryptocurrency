#ifndef QUEUE_H
#define QUEUE_H

#include "singlylinkedlist.cpp"

template<typename T>
class Queue {
    public:
        void enqueue(T value);
        T dequeue();
        T getFront();
        unsigned int getLength();
    private:
        SinglyLinkedList<T> list;
};

#endif