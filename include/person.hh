#ifndef PLAYER_HH
#define PLAYER_HH

#include "linked_list.hh"
#include <iostream>
#include <proxy.hh>
#include <queue>
#include <string>

enum MovementType { RANDOM = 1, ADJACENT, THROUGH_ALL, DIRECT };

class Person {
  static int next_id;

public:
  int id = next_id++;
  std::string name;
  MovementType mode;
  LinkedList<Proxy<Person>> *friends = nullptr;
  Person *next = nullptr;

  int steps = 0;
  class Arc *currentArc = nullptr;
  class Node *prev = nullptr;
  class Node *from = nullptr;
  class Node *to = nullptr;

  // Shortest path variables
  int shortestTime = 0;
  bool hasPath = false;
  std::queue<class Node *> path = std::queue<class Node *>();

  Person(std::string name, Node from, Node to, MovementType mode);
  Person(std::string name, MovementType mode);

  bool addFriend(Person *person);

  Arc *nextArc();

  void shortestPath(Node *from, Node *to, int time = 0);

  std::string toString();
};

// La aleatoria, a cualquiera menos al anterior
//
#endif
