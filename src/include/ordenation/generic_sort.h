#pragma once
#ifndef GENERIC_SORT_H
#define GENERIC_SORT_H

#include "../structure/doubly_linked_list.h"

template <typename T>
class GenericSort {
    protected:
        virtual int compare(T data1, T data2) = 0;
    public:
        virtual void sort(DoublyLinkedList<T> &list) = 0;
};

#endif