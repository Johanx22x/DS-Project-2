#include <cstdio>
#include <graph.hh>
#include <iostream>
#include <linked_list.hh>
#include <person.hh>
#include <queue>
#include <string>

#define INF 1000

int Person::next_id = 0;

std::string Person::toString() {
  std::string result = "Person (" + std::to_string(id) + "): " + name;
  return result;
}

bool Person::addFriend(Person *person) {
  (void)person;
  /* if (friends == nullptr) friends = new LinkedList<Person>(); */

  /* // Check if the new friend is already in the list */
  /* Person *curr = friends->head; */
  /* while (curr != nullptr) { */
  /*   if (curr->id == person->id) return false; */
  /*   curr = curr->next; */
  /* } */

  /* // Add the new friend to the list */
  /* friends->add(person); */

  /* return true; */
  return false;
}

// Function to store the shortest path in the person queue called 'path'
// If doesn't exist a path, the queue will be empty
//
// @param person: The person to store the path
// @param from: The node where the person is located
// @param to: The node where the person wants to go
// @param alt_path: The alternative path to the person 
// @param last_node: The last node of the alternative path
void Person::shortestPath(Node *from, Node *to, int time, std::queue<Node *> alt_path, Node *last_node) {
  if (last_node != nullptr) {
    alt_path.push(last_node);
  }

  // If the node is already visited or from is null, return
  if (from == nullptr || from->visited)
    return;

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
    if (this->from->arcs == nullptr) {
      return nullptr;
    }

    // If only one arc exists, return it
    if (this->from->arcs->size < 2) {
      if (this->from->arcs->head == nullptr) {
        return nullptr;
      }
      return this->from->arcs->head->link;
    }

    // Get a random number between 0 and the number of arcs
    int random = rand() % this->from->arcs->size;

    // Get the arc in the random position
    Proxy<Arc> *curr = this->from->arcs->head;
    Proxy<Arc> *prev = nullptr;
    for (int i = 0; i < random; i++) {
      prev = curr;
      curr = curr->next;
    }

    if (curr->link->to == this->prev) {
      if (curr->next != nullptr) {
        curr = curr->next;
      } else if (prev != nullptr) {
        curr = prev;
      } else {
        curr = this->from->arcs->head;
      }
    }

    return curr->link;
  } else if (mode == MovementType::ADJACENT) {
    if (this->from->arcs == nullptr) {
      return nullptr;
    }

    if (this->from->arcs->size < 2) {
      if (this->from->arcs->head == nullptr) {
        return nullptr;
      }
      return this->from->arcs->head->link;
    }
    Arc *shortest = this->from->arcs->head->link;

    for (Proxy<Arc> *tmp = this->from->arcs->head; tmp != nullptr;
         tmp = tmp->next) {
      if (tmp->link->time < shortest->time)
        shortest = tmp->link;
    }

    if (shortest == this->currentArc && shortest->next != nullptr) {
      shortest = shortest->next;
      for (Proxy<Arc> *tmp = this->from->arcs->head; tmp != nullptr;
           tmp = tmp->next) {
        if (tmp->link->time < shortest->time && tmp->link != this->currentArc)
          shortest = tmp->link;
      }
    }

    return shortest;

  } else if (mode == MovementType::THROUGH_ALL) {
    // create a matrix that contains all nodes
    if (this->path.empty())
      return nullptr;

    Node *nextNode = this->path.front();
    this->path.pop();

    for (Proxy<Arc> *curr = this->from->arcs->head; curr != nullptr;
         curr = curr->next) {
      if (curr->link->to == nextNode) {
        return curr->link;
      }
    }

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
