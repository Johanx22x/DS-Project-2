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
void Person::shortestPath(Node *from, Node *to, int time, std::queue<Node *> alt_path, Node *last_node) {
  if (last_node != nullptr) {
      alt_path.push(last_node);
  }

  // If the node is already visited or from is null, return
  if (from == nullptr || from->visited) return;

  // If the node is the destination
  if (from == to) {
    // If the time is less than the shortest time, update the shortest time
    if (this->shortestTime == 0 || time < this->shortestTime) {
      this->shortestTime = time;
      alt_path.push(to);
      this->path = alt_path;
    }
    this->hasPath = true;
    return;
  }

  from->visited = true;

  // For each arc in the node
  Proxy<Arc> *curr = from->arcs->head;
  while (curr != nullptr) {
    // Call the function recursively
    shortestPath(curr->link->to, to, time + curr->link->time, alt_path, from);

    curr = curr->next;
  }

  // Unmark the node as visited
  from->visited = false;
}

Arc *Person::nextArc() {
  if (mode == MovementType::RANDOM) {
    // If only one arc exists, return it
    if (this->from->arcs->size < 2) {
      return this->from->arcs->head->link;
    }

    std::cout << "DEBUG: RANDOM 1\n";

    // Get a random number between 0 and the number of arcs
    int random = rand() % this->from->arcs->size;

    std::cout << "DEBUG: RANDOM 2\n";

    // Get the arc in the random position
    Proxy<Arc> *curr = this->from->arcs->head;
    Proxy<Arc> *prev = nullptr;
    for (int i = 0; i < random; i++) {
      prev = curr;
      curr = curr->next;
    }

    std::cout << "DEBUG: RANDOM 3\n";

    if (curr->link->to == this->prev) {
      if (curr->next != nullptr) {
        curr = curr->next;
      } else if (prev != nullptr) {
        curr = prev;
      } else {
        curr = this->from->arcs->head;
      }
    }

    std::cout << "DEBUG: RANDOM 4\n";

    return curr->link;
  } else if (mode == MovementType::ADJACENT) {
    Arc *shortest = this->from->arcs->head->link;

    std::cout << "DEBUG: ADJACENT 1\n";

    for (Proxy<Arc> *tmp = this->from->arcs->head; tmp != nullptr;
         tmp = tmp->next) {
      if (tmp->link->time < shortest->time)
        shortest = tmp->link;
    }

    std::cout << "DEBUG: ADJACENT 2\n";

    if (shortest == this->currentArc && shortest->next != nullptr) {
      shortest = shortest->next;
      for (Proxy<Arc> *tmp = this->from->arcs->head; tmp != nullptr;
           tmp = tmp->next) {
        if (tmp->link->time < shortest->time && tmp->link != this->currentArc)
          shortest = tmp->link;
      }
    }

    std::cout << "DEBUG: ADJACENT 3\n";

    return shortest;

  } else if (mode == MovementType::THROUGH_ALL) {
    return nullptr;
  } else if (mode == MovementType::DIRECT) {
    if (this->path.empty()) {
      return nullptr;
    }

    std::cout << "DEBUG: DIRECT 1\n";

    Node *nextNode = this->path.front();
    this->path.pop();

    std::cout << "DEBUG: DIRECT 2\n";

    Proxy<Arc> *curr = this->from->arcs->head;
    while (curr != nullptr) {
      if (curr->link->to == nextNode) {
        return curr->link;
      }
      curr = curr->next;
    }

    std::cout << "DEBUG: DIRECT 3\n";
  }

  return nullptr;
}
