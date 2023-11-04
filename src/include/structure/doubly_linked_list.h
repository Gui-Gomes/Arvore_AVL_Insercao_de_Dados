#pragma once
#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

using namespace std;

// ESTRUTURA DO NÓ DA LISTA.
template <typename T>
struct node
{
    T data;
    node<T> *next = nullptr;
    node<T> *previous = nullptr;
};

// ESTRUTURA DA LISTA DUPLAMENTE ENCADEADA.
template <typename T>
class DoublyLinkedList
{
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

// CONSTRUTOR INICIANDO OS ATRIBUTOS.
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
    start = nullptr;
    end = nullptr;
    count = 0;
}

// DESCONSTRUTOR.
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    while (size() > 0)
    {
        pop();
    }
}

// MÉTODO RESPONSÁVEL POR RETORNAR UM PONTEIRO PARA O NÓ NA POSIÇÃO INFORMADA.
template <typename T>
node<T> *DoublyLinkedList<T>::getNode(int position)
{
    if (position < 0 || position > size() - 1)
        return nullptr;

    node<T> *aux;
    if (position > size() / 2)
    {
        aux = end;
        for (int i = size() - 1; i > position; i--)
            aux = aux->previous;
    }
    else
    {
        aux = start;
        for (int i = 0; i < position; i++)
            aux = aux->next;
    }
    return aux;
}

// MÉTODO RESPONSÁVEL POR ADICIONAR DETERMINADO DADO NO FINAL DA LISTA.
template <typename T>
void DoublyLinkedList<T>::pushBack(T data)
{
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

// MÉTODO RESPONSÁVEL POR ADICIONAR DETERMINADO DADO NA LISTA. PODE-SE INSERIR EM QUALQUER POSIÇÃO DA LISTA, BASTA POSITION ESTAR ENTRE 0 E SIZE().
template <typename T>
void DoublyLinkedList<T>::append(T data, int position)
{
    if (position < 0 || position > size())
    {
        count--;
        throw out_of_range("Position out of bounds");
    }
    node<T> *newNode = new node<T>();
    newNode->data = data;
    if (position == 0)
    {
        newNode->next = start;
        newNode->previous = nullptr;
        if (start != nullptr)
        {
            start->previous = newNode;
        }
        start = newNode;
        if (end == nullptr)
        {
            end = newNode;
        }
    }
    else if (position == size())
    {
        newNode->next = nullptr;
        newNode->previous = end;
        if (end != nullptr)
        {
            end->next = newNode;
        }
        end = newNode;
    }
    else
    {
        node<T> *aux = getNode(position);
        newNode->next = aux;
        newNode->previous = aux->previous;
        aux->previous->next = newNode;
        aux->previous = newNode;
    }
    count++;
}

// MÉTODO RESPONSÁVEL POR DELETAR O NÓ NA POSIÇÃO INFORMADA.
template <typename T>
void DoublyLinkedList<T>::deleteNode(int position)
{
    node<T> *aux = getNode(position);
    if (!aux)
    {
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

// MÉTODO RESPONSÁVEL POR DELETAR O ÚLTIMO NÓ DA LISTA.
template <typename T>
void DoublyLinkedList<T>::pop()
{
    deleteNode(size() - 1);
}

// MÉTODO RESPONSÁVEL POR TROCAR 2 NÓS DE POSIÇÃO NA LISTA.
template <typename T>
void DoublyLinkedList<T>::switchNodes(int position1, int position2)
{
    node<T> *node1 = getNode(position1);
    node<T> *node2 = getNode(position2);
    if (!node1 || !node2)
    {
        throw out_of_range("Position out of bounds");
    }
    T aux = node1->data;
    node1->data = node2->data;
    node2->data = aux;
}

// MÉTODO RESPONSÁVEL POR RETORNAR O DADO CONTIDO NO NÓ INFORMADO.
template <typename T>
T DoublyLinkedList<T>::getValue(int position)
{
    node<T> *aux = getNode(position);
    if (aux)
    {
        return aux->data;
    }
    throw out_of_range("Position out of bounds");
}

// MÉTODO RESPONSÁVEL POR IMPRIMIR A LISTA.
template <typename T>
void DoublyLinkedList<T>::printList(void (*printFunction)(T))
{
    node<T> *aux = start;
    for (int i = 0; i < size(); i++)
    {
        printFunction(aux->data);
        aux = aux->next;
    }
}

// MÉTODO RESPONSÁVEL POR IMPRIMIR O DADO PRESENTE NO NÓ DA POSIÇÃO INFORMADA.
template <typename T>
void DoublyLinkedList<T>::printOneNode(void (*printFunction)(T), int position)
{
    node<T> *aux = getNode(position);
    if (aux)
    {
        printFunction(aux->data);
    }
}

// MÉTODO RESPONSÁVEL POR RETORNAR O TAMANHO DA LISTA.
template <typename T>
int DoublyLinkedList<T>::size()
{
    return count;
}

#endif