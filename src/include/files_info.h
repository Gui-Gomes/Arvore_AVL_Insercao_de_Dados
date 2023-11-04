#pragma once
#ifndef FILES_INFO_H
#define FILES_INFO_H

#include <string>
#include "structure/doubly_linked_list.h"

struct filesInfo
{
    std::string fileName;
    DoublyLinkedList<int> *lines;
};

#endif