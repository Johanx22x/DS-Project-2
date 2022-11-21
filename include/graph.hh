#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <linked_list.hh>
#include <person.hh>
#include <proxy.hh>
#include <queue>
#include <string>

class Node {
    public:
  static int next_id;
  bool visited = false;
  int id = next_id++;
  std::string name;
  Node *next = nullptr;
  std::queue<Person *> people = std::queue<Person *>();
  LinkedList<Proxy<class Arc>> *arcs = new LinkedList<Proxy<class Arc>>();

  Node(std::string name) : name(name) {}
  Node(){};

  /**
   * Prints a stringified version of the node
   */
  void toString();
};

class Arc {
    public:
  static int next_id;
  int id = next_id++;
  int time = 0;
  Node *to;

  Arc *next = nullptr;

  Arc(int time, Node *to) : time(time), to(to) {}

  /**
   * Prints a stringified version of the arc
   */
  void toString();
};

#endif
