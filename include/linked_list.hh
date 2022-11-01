#ifndef LINKED_LIST_HH
#define LINKED_LIST_HH

#include <iostream>
#include <string>

template <class T>
class LinkedList {
    T *list = nullptr;
    T head = nullptr;
    T tail = nullptr;
public:
    int size = 0;

    LinkedList() = default;

    LinkedList(T *list, int size) : list(list), size(size) {}

    void add(T item);

    void remove(T item);

    T* find(int id);

    void print();
};

#endif
