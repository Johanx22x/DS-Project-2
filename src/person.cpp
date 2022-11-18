#include <cstdio>
#include <iostream>
#include <linked_list.hh>
#include <person.hh>
#include <string>

int Person::next_id = 0;

std::string Person::toString() {
  std::string result = "Person (" + std::to_string(id) + "): " + name;
  return result;
}

bool Person::addFriend(Person *person) {
  // Check if the new friend is already in the list
  Proxy<Person> *curr = friends->head;
  while (curr != NULL) {
    if (curr->link == person) {
      return false;
    }
    curr = curr->next;
  }

  // Add the new friend to the list
  if (friends == nullptr) {
    /* friends = new LinkedList<Proxy<Person>, 1>(Proxy<Person>(person)); */
    friends = new LinkedList<Proxy<Person>>();
  } else {
    friends->add(new Proxy<Person>(person));
  }

  return true;
}

Arc *Person::nextArc() {
  return nullptr;
}
