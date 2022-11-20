#ifndef LINKED_LIST_HH
#define LINKED_LIST_HH

#include <algorithm>
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
      tail->next = nullptr;
  }

  size++;
}

// fun fact: this had a memory leak
template <class T> void LinkedList<T>::remove(T *item) {
  if (item == nullptr || head == nullptr) {
    return;
  }

  if (tail == item) {
    tail = nullptr;
    T *current = head;
    while (current->next != item) current = current->next;
    current->next = nullptr;
    tail = current;
    return;
  }

  T *curr = head;
  T *prev = nullptr;
  while (curr != nullptr) {
    if (curr == item && prev) {
      prev->next = curr->next;
      delete curr;
      size--;
      return;
    }
    if (curr == item && !prev) {
      head = head->next;
      delete curr;
      size--;
      return;
    }
    if (curr == tail) {
      tail = prev;
      if (tail) {
        tail->next = nullptr;
      }
    }

    prev = curr;
    curr = curr->next;
  }
}

template <class T> T *LinkedList<T>::find(int id) {
  if (head == nullptr) return head;
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
