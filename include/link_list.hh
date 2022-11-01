#ifndef LINK_LIST_HH
#define LINK_LIST_HH

#include <iostream>
#include <string>

template <class T>
class LinkList {
    T *list = nullptr;
    int size = 0;
    T head = nullptr;
    T tail = nullptr;

public:

    LinkList() = default;

    LinkList(T *list, int size) : list(list), size(size) {}

    void add(T item);

    void remove(T item);

    void find(T item);

    void print();
};

#endif
