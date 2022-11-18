#include <cstdio>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>
#include <person.hh>
#include <queue>
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

// Function to store the shortest path in the person queue called 'path'
// If doesn't exist a path, the queue will be empty
//
// @param person: The person to store the path
// @param from: The node where the person is located
// @param to: The node where the person wants to go
void Person::shortestPath(Node *from, Node *to, int time) {
  // If the node is already visited or from is null, return
  if (from->visited || from == nullptr) {
    return;
  }

  // If the node is the destination
  if (from == to) {
    // If the time is less than the shortest time, update the shortest time
    if (this->shortestTime == 0 || time < this->shortestTime) {
      this->shortestTime = time;
      this->path.push(to);
    }
    this->hasPath = true;
    return;
  }

  // Mark the node as visited
  from->visited = true;

  // For each arc in the node
  Proxy<Arc> *curr = from->arcs->head;
  while (curr != nullptr) {
    shortestPath(curr->link->to, to, time + curr->link->time);
    curr = curr->next;
  }

  // Unmark the node as visited
  from->visited = false;
}

Arc *Person::nextArc() {
  if (mode == MovementType::RANDOM) {
    if (this->from->arcs->size < 2) {
      return this->from->arcs->head->link;
    }

    for (Proxy<Arc> *tmp = this->from->arcs->head; tmp != nullptr;
         tmp = tmp->next) {

      if (tmp->link == this->currentArc)
        continue;

      return tmp->link;
    }

  } else if (mode == MovementType::ADJACENT) {
    return nullptr;
  } else if (mode == MovementType::THROUGH_ALL) {
    return nullptr;
  } else if (mode == MovementType::DIRECT) {
    if (this->path.empty()) {
      return nullptr;
    }

    Node *nextNode = this->path.front();
    this->path.pop();

    Proxy<Arc> *curr = this->from->arcs->head;
    while (curr != nullptr) {
      if (curr->link->to == nextNode) {
        return curr->link;
      }
      curr = curr->next;
    }
  }

  return nullptr;
}
