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

template <class T> void LinkedList<T>::remove(T *item) {
  if (item == nullptr) {
    return;
  }

  if (head == item) {
    head = head->next;
    size--;
    return;
  }

  T *curr = head->next;
  T *prev = head;
  while (curr != nullptr) {
    if (curr == item) {
      prev = curr->next;
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
