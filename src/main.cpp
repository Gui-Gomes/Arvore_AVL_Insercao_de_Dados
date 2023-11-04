#include <iostream>
#include "include/structure/avl_tree.h"
#include "ordenation/quick_sort.h"

// IMPLEMENTAÇÃO DA INTERFACE QUICKSORT PARA ORGANIZAR STRINGS
class StringQuickSort : public QuickSort<string>
{
    virtual int sort(string word1, string word2)
    {
        return word1.compare(word2);
    }
};

int main()
{
    AVLTree<string> words;
}