#ifndef PLAYER_HH
#define PLAYER_HH

#include "linked_list.hh"
#include <iostream>
#include <proxy.hh>
#include <queue>
#include <string>
#include <vector>

enum MovementType { RANDOM, ADJACENT, THROUGH_ALL, DIRECT };

class Person {
public:
  static int next_id;
  int id = next_id++;
  std::string name;
  MovementType mode;
  std::vector<Person*> *friends = new std::vector<Person*>();
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
  bool hasPath = false;
  std::queue<class Node *> path = std::queue<class Node *>();

  Person(std::string name, Node *from, Node *to, MovementType mode)
      : name(name), mode(mode), from(from), to(to) {}
  Person(std::string name, MovementType mode) : name(name), mode(mode) {}

  /**
   * Adds a friend to this user's friends list
   *
   * @param person The friend to be added
   * @return Whether or not the friend was actually added
   */
  bool addFriend(Person *person);

  /**
   * Returns the next arc where the user should move
   *
   * @return The next arc
   */
  Arc *nextArc();

  /**
   * Calculates and sets the shortest path between 2 nodes
   *
   * @param from The origin node
   * @param to The destination node
   * @param time The current time within an arc
   */
  void shortestPath(Node *from, Node *to, int time = 0,
                    std::queue<Node *> alt_path = std::queue<Node *>(),
                    Node *last_node = nullptr);

  /**
   * Returns a string representation of the current person
   *
   * @return A string representation of the current person
   */
  std::string toString();
};

// La aleatoria, a cualquiera menos al anterior
//
#endif
