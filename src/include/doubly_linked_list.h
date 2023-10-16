#pragma once
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

using namespace std;

template <typename T>
struct node {
    T data;
    node<T> *next = nullptr;
    node<T> *previous = nullptr;
};

template <typename T>
class DoublyLinkedList {
    private:
        node<T> *start;
        node<T> *end;
        node<T> *getNode(int position);
        int count;
    
    public:
        DoublyLinkedList();
        ~DoublyLinkedList();

        void pushBack(T data);
        void append(T data, int position);
        void deleteNode(int position);
        void pop();
        void switchNodes(int position1, int position2);
        void printList(void (*printFunction)(T));
        void printOneNode(void (*printFunction)(T), int postion);

        T getValue(int position);

        int size();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    start = nullptr;
    end = nullptr;
    count = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (size() > 0) {
        pop();
    }
}

template <typename T>
node<T> *DoublyLinkedList<T>::getNode(int position) {
    if (position < 0 || position > size() - 1)
        return nullptr;
    
    node<T> *aux;
    if (position > size() / 2) {
        aux = end;
        for (int i = size() - 1; i > position; i--)
            aux = aux->previous;
    }
    else {
        aux = start;
        for (int i = 0; i < position; i++)
            aux = aux->next;
    }
    return aux;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(T data) {
    node<T> *aux = new node<T>();
    aux->data = data;
    aux->previous = end;
    if (start == nullptr)
        start = aux;
    if (end != nullptr)
        end->next = aux;
    end = aux;
    count++;
}

template <typename T>
void DoublyLinkedList<T>::append(T data, int position) {
    node<T> *newNode = new node<T>();
    node<T> *aux = getNode(position);
    if (position > 0 && position < size() - 1) {
        newNode->data = aux->data;
        aux->data = data;
        aux->next->previous = newNode;
        newNode->next = aux->next;
        newNode->previous = aux;
        aux->next = newNode;
    }
    else if (position == 0) {
        newNode->data = start->data;
        start->data = data;
        start->next->previous = newNode;
        newNode->next = start->next;
        newNode->previous = start;
        start->next = newNode;
    }
    else if (position == size() - 1) {
        newNode->data = end->data;
        end->data = data;
        newNode->previous = end;
        end->next = newNode;
        end = newNode;
    }
    else {
        count--;
        throw out_of_range("Position out of bounds");
    }
    count++;
}

template <typename T>
void DoublyLinkedList<T>::deleteNode(int position) {
    node<T>* aux = getNode(position);
    if (!aux) {
        throw out_of_range("Position out of bounds");
    }
    if (aux->next != nullptr)
        aux->next->previous = aux->previous;
    if (aux->previous != nullptr)
        aux->previous->next = aux->next;
    if (position == 0)
        start = aux->next;
    if (position == size() - 1)
        end = aux->previous;
    delete aux;
    count--;
}

template <typename T>
void DoublyLinkedList<T>::pop() {
    deleteNode(size() - 1);
}

template <typename T>
void DoublyLinkedList<T>::switchNodes(int position1, int position2) {
    node<T>* node1 = getNode(position1);
    node<T>* node2 = getNode(position2);
    if (!node1 || !node2) {
        throw out_of_range("Position out of bounds");
    }
    T aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
}

template <typename T>
T DoublyLinkedList<T>::getValue(int position)
{
    node<T> *aux = getNode(position);
    if (aux) {
        return aux->data;
    }
    throw out_of_range("Position out of bounds");
}

template <typename T>
void DoublyLinkedList<T>::printList(void (*printFunction)(T))
{
    node<T>* aux = start;
    for (int i = 0; i < size(); i++)
    {
        printFunction(aux->data);
        aux = aux->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::printOneNode(void (*printFunction)(T), int position) {
    node<T>* aux = getNode(position);
    if (aux) {
        printFunction(aux->data);
    }
}

template <typename T>
int DoublyLinkedList<T>::size() {
    return count;
}

#endif