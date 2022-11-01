#include <cstdio>
#include <iostream>
#include <string>
#include <linked_list.hh>

template <class T>
void LinkedList<T>::add(T item) {
    if (list == nullptr) {
        list = item;
        head = item;
        tail = item;
        size++;

        return;
    } 
    
    tail->next = item;
    tail = item;
    size++;
    return;
}

template <class T>
void LinkedList<T>::remove(T item) {
    if (list == item) {
        list = head->next;
        head = list;
        return;
    }

    T *curr = list->next;
    T *prev = list;
    while (curr != nullptr) {
        if (curr == item) {
            prev = curr->next;
            return;
        }

        prev = curr;
        curr = curr->next;
    }
}

template <class T>
T* LinkedList<T>::find(int id) {
    if (head->id == id) {
        return head;
    }

    T *curr = list->next;
    while (curr != nullptr) {
        if (curr->id == id) {
            return curr;
        }
        curr = curr->next;
    }

    return nullptr;
}

template <class T>
void LinkedList<T>::print() {
    T *curr = head;

    while (curr != nullptr) {
        std::cout << curr << "\n";
        curr = curr->next;
    }
}
