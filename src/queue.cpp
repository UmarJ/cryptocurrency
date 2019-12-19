#include "queue.h"

template<typename T>
void Queue<T>::enqueue(T value) {
    list.insertAtTail(value);
}

template<typename T>
T Queue<T>::dequeue() {
    T temp = list.getHeadValue();
    list.deleteHead();
    return temp;
}

template<typename T>
T Queue<T>::getFront() {
    return list.getHeadValue();
}

template<typename T>
unsigned int Queue<T>::getLength() {
    return list.getLength();
}