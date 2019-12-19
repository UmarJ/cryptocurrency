#include "singlylinkedlist.h"

template<typename T>
SinglyLinkedList<T>::Node::Node(T value, Node* next) : value(value), next(next) {}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() {
    return head == nullptr;
}

template<typename T>
void SinglyLinkedList<T>::setTail(Node* newTail) {
    tail->next = newTail; // set the new tail as previous tail's next
    newTail->next = nullptr;
    tail = newTail;
}

template<typename T>
void SinglyLinkedList<T>::insertAtHead(T value) { // method to insert a value at the head
    Node* newNode = new Node(value, head);

    if (isEmpty()) {
        tail = newNode;
    }
    
    head = newNode;
    length++;
}
template<typename T>
void SinglyLinkedList<T>::insertAtTail(T value) {

    if (isEmpty()) {
        insertAtHead(value); // inserting at head is the same as inserting at the tail when the list is empty
        return;
    }

    Node* newNode = new Node(value, nullptr);
    setTail(newNode);
    length++;
}

template<typename T>
void SinglyLinkedList<T>::insertAtIndex(int index, T value) { // method to insert a node at a specified location
            
    Node* currentNode = head;
    Node* previousNode = nullptr;
    int currentIndex = 0;

    if (index > length) { // check if invalid location is entered
        return;
    }

    if (index == 0) {
        insertAtHead(value);
        return;
    }

    if (index == length - 1) {
        insertAtTail(value);
        return;
    }

    while(currentIndex < index) { // traverse the list until the required location is reached
        previousNode = currentNode;
        currentNode = currentNode->next;
        currentIndex++;
    }

    Node* newNode = new Node(value, currentNode); // create a new node
    previousNode->next = newNode;

    length++; // increment the length
}

template<typename T>
void SinglyLinkedList<T>:: deleteNodeAt(int location) { // method to delete node from a certain location

    Node* currentNode = head;
    Node* previousNode = nullptr;
    int currentIndex = 0;

    if (location >= length) { // check if invalid location is entered
        return;
    }

    while(currentIndex < location) { // traverse the list until the required location is reached
        previousNode = currentNode;
        currentNode = currentNode->next;
        currentIndex++;
    }

    if (currentIndex == 0) { // check if the node to be deleted is the head
        head = currentNode->next;
    }

    else if (currentIndex == length - 1) { // check if the node to be deleted is the tail
        setTail(previousNode);
    }

    else {
        previousNode->next = currentNode->next;
    }
    
    delete currentNode;
    length--; // decrement the length
}

template<typename T>
void SinglyLinkedList<T>:: deleteHead() {
    deleteNodeAt(0);
}

template<typename T>
void SinglyLinkedList<T>::deleteTail() {
    deleteNodeAt(length - 1);
}

template<typename T>
unsigned int SinglyLinkedList<T>::getLength() {
    return length;
}

template<typename T>
T SinglyLinkedList<T>::getHeadValue() {
    return head->value;
}