#pragma once
#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "generic_sort.h"

template <typename T>
class QuickSort : public GenericSort<T> {
    private:
        void sort(DoublyLinkedList<T> &list, int left, int right);
    public:
        virtual void sort(DoublyLinkedList<T> &list);
};

template <typename T>
void QuickSort<T>::sort(DoublyLinkedList<T> &list, int left, int right) {
    int i = left, j = right;
    T pivot = list.getValue((i + j) / 2);
    while (i <= j) {
        while (this->compare(list.getValue(i), pivot) < 0)
            i++;
        while (this->compare(list.getValue(j), pivot) > 0)
            j--;
        if (i <= j) {
            list.switchNodes(i, j);
            i++;
            j--;
        }
    }
    if (left < j)
        sort(list, left, j);
    if (i < right)
        sort(list, i, right);
}

template <typename T>
void QuickSort<T>::sort(DoublyLinkedList<T> &list) {
    this->sort(list, 0, list.getSize() - 1);
}

#endif