#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

template <typename T>
class SinglyLinkedList {
    public:
        void insertAtHead(T value);
        void insertAtTail(T value);
        void insertAtIndex(int index, T value);
        void deleteNodeAt(int index);
        void deleteHead();
        void deleteTail();
        unsigned int getLength();
        T getHeadValue();

    private:
        struct Node {
            T value;
            Node* next;
            Node(T value, Node* next = nullptr);
        };

        unsigned int length = 0;
        Node* head = nullptr;
        Node* tail = nullptr;
        bool isEmpty();
        void setTail(Node* newTail);

};

#endif