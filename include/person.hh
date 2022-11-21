#ifndef PLAYER_HH
#define PLAYER_HH

#include "linked_list.hh"
#include <iostream>
#include <proxy.hh>
#include <queue>
#include <string>

enum MovementType { RANDOM, ADJACENT, THROUGH_ALL, DIRECT };

class Person {
public:
  static int next_id;
  int id = next_id++;
  std::string name;
  MovementType mode;
  LinkedList<Person> *friends = new LinkedList<Person>();
  Person *next = nullptr;

  int steps = 0;
  class Arc *currentArc = nullptr;
  class Node *prev = nullptr;
  class Node *from = nullptr;
  class Node *to = nullptr;

  bool inSimulation = false;
  bool inNode = false;

  // Shortest path variables
  int shortestTime = 0;
  bool hasPath = true;
  std::queue<class Node *> path = std::queue<class Node *>();

  Person(std::string name, Node *from, Node *to, MovementType mode)
      : name(name), mode(mode), from(from), to(to) {}
  Person(std::string name, MovementType mode) : name(name), mode(mode) {}

  bool addFriend(Person *person);

  Arc *nextArc();

  void shortestPath(Node *from, Node *to, int time = 0,
                    std::queue<Node *> alt_path = std::queue<Node *>(),
                    Node *last_node = nullptr);

  std::string toString();
};

// La aleatoria, a cualquiera menos al anterior
//
#endif
