#ifndef LINKED_LIST_HH
#define LINKED_LIST_HH

#include <iostream>
#include <string>

template <typename T> class LinkedList {

public:
  T *head = nullptr;
  T *tail = nullptr;

  int size = 0;

  LinkedList() = default;

  LinkedList(T *list, int size) : head(list), size(size) {}

  void add(T *item);

  void remove(T *item);

  T *find(int id);

  void print();
};

#include <cstdio>

template <class T> void LinkedList<T>::add(T *item) {
  if (head == nullptr) {
    head = item;
    tail = item;
  } else {
    tail->next = item;
    tail = item;
  }

  size++;
}

// fun fact: this had a memory leak
template <class T> void LinkedList<T>::remove(T *item) {
    std::cout << "Removing " << item->id << "\n";
  if (item == nullptr) {
    return;
  }

  T *tmp = head;
  if (head == item) {
    head = head->next;

    delete tmp;

    size--;
    return;
  }

  T *curr = head->next;
  T *prev = head;
  while (curr != nullptr) {
    if (curr == item) {
      tmp = curr;
      prev = curr->next;

      delete tmp;

      size--;
      return;
    }

    prev = curr;
    curr = curr->next;
  }
}

template <class T> T *LinkedList<T>::find(int id) {
  if (head->id == id) {
    return head;
  }

  T *curr = head->next;
  while (curr != nullptr) {
    if (curr->id == id) {
      return curr;
    }
    curr = curr->next;
  }

  return nullptr;
}

template <class T> void LinkedList<T>::print() {
  T *curr = head;

  while (curr != nullptr) {
    std::cout << curr << "\n";
    curr = curr->next;
  }
}

#endif
